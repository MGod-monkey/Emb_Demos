<?php
/*
 * @Author: your name
 * @Date: 2021-08-28 16:41:27
 * @LastEditTime: 2021-09-06 22:18:09
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Desktop\tts.php
 */

//获取token
require __DIR__ . '/vendor/autoload.php';
use AlibabaCloud\Client\AlibabaCloud;
use AlibabaCloud\Client\Exception\ClientException;
use AlibabaCloud\Client\Exception\ServerException;

header('Content-Type:application/json');
$ip = getIP(true);
$accessKeyID = 'LTAI5tSWxLTbb6qbyM7qPz2q';
$accessKeySecret = 'WEAO1K2YWPBBujCDnuEvfUaUPTOjZY';
$appkey = "pPYuSdQYqjYmQzF5";
$token = NULL;


AlibabaCloud::accessKeyClient(
    $accessKeyID,
    $accessKeySecret)
    ->regionId("cn-shanghai")
    ->asDefaultClient();

try {
    $response = AlibabaCloud::nlsCloudMeta()
                        ->v20180518()
                        ->createToken()
                        ->request();
    $token = $response["Token"]['Id'];
    if ($token == NULL) {
        $results['error'] = 1;
        $results['reason'] = '获取token失败！';
        echo json_encode($results, JSON_UNESCAPED_UNICODE);
    }
    else {$results['token'] = $token;}
} catch (ClientException $exception) {
    // 获取错误消息
    $results['error'] = 1;
    $results['reason'] = $exception->getErrorMessage();
    echo json_encode($results, JSON_UNESCAPED_UNICODE);
} catch (ServerException $exception) {
    // 获取错误消息
    $results['error'] = 1;
    $results['reason'] = $exception->getErrorMessage();
    echo json_encode($results, JSON_UNESCAPED_UNICODE);
}



// 定义一些默认配置
$_audioDir = '/var/www/html/tts/';   //语音文件存放目录
$errorText = '哎呀！发生了一点小错误！';       //发生错误时，说的话
$format_default = "mp3";     //请求的音频格式,可选'wav'
$sampleRate_default = 16000;    //采样率
$volume_default = 100;          //音量0~100
$voice_default = 'maoxiaomei';  //发言人
$speechRate_default = 0;       //语速-500~500
$pitchRate_default = 0;        //语调-500~500

$results = array('error' => 0, 'timestamp' => 0, 'token' => '', 'time' => 0, 'reason' => '', 'task_array' => array(), 
                            'audio_path' => '/var/www/html/error.mp3', 'audio_url' => $ip . 'error.mp3');

//请求参数见：https://help.aliyun.com/document_detail/94737.html#title-fmu-0zs-vda
//在线调试见：https://help.aliyun.com/document_detail/214623.html


// 从Post请求中获取配置
$text = empty($_POST['text'])?$errorText:$_POST['text'];
$textUrlEncode = urlencode($text);
$textUrlEncode = preg_replace('/\+/', '%20', $textUrlEncode);
$textUrlEncode = preg_replace('/\*/', '%2A', $textUrlEncode);
$textUrlEncode = preg_replace('/%7E/', '~', $textUrlEncode);
$format = empty($_POST['format'])?$format_default:$_POST['format'];
$sampleRate = empty($_POST['sampleRate'])?$sampleRate_default:$_POST['sampleRate'];
$volume = empty($_POST['volume'])?$volume_default:$_POST['volume'];
$voice = empty($_POST['voice'])?$voice_default:$_POST['voice'];
$speech_rate = empty($_POST['speech_rate'])?$speechRate_default:$_POST['speech_rate'];
$pitch_rate = empty($_POST['pitch_rate'])?$pitchRate_default:$_POST['pitch_rate'];



if(createDir($_audioDir) || $results['error']==0) {
    $fileUrl = $ip . 'tts/';
    processPOSTRequest($appkey, $token, $text, $_audioDir, $format, 
                            $sampleRate, $voice, $volume, $speech_rate, $pitch_rate, $fileUrl);
}


// 获取ip
function getIP($isExternal){
    if ($isExternal){
        $externalContent = file_get_contents('http://checkip.dyndns.com/');	//获取公网IP地址
        preg_match('/Current IP Address: \[?([:.0-9a-fA-F]+)\]?/', $externalContent, $m);
        $ip = 'http://' . $m[1] . '/';
    } else{
        $ip = 'http://' . $_SERVER["REMOTE_ADDR"];	//获取内网IP地址
    }
    return $ip;
}

// 采用MD5(时间撮)加密获得当前语音的文件名
function getFileNameByMd5($nowtime, $format){
    $encrypt_str = substr(md5($nowtime), 8, 16) . '.' . $format;
    return $encrypt_str;
}

// 创建存放音频文件的文件夹
function createDir($filePath){
    $_filePath = iconv('utf-8', 'gb2312', $filePath);
    if (file_exists($_filePath) == false){  //文件夹不存在则创建目录
        if (mkdir($_filePath, 0777, true)){
            return true;
        }
        else {
            $results['error'] = 1;
            $results['reason'] = '文件目录创建失败！';
            echo json_encode($results, JSON_UNESCAPED_UNICODE);
            return false;
        }
    }
    else {
        return true;
    }
}
// 发起post请求
function processPOSTRequest($appkey, $token, $text, $_audioDir, $format, 
                                    $sampleRate, $voice, $volume, $speech_rate, $pitch_rate, $fileUrl) {
    $url = "https://nls-gateway.cn-shanghai.aliyuncs.com/stream/v1/tts";
    /**
     * 请求参数，以JSON格式字符串填入HTTPS POST请求的Body中。
     */
    $taskArr = array(
        "appkey" => $appkey,
        "token" => $token,
        "text" => $text,
        "format" => $format,
        "sample_rate" => $sampleRate,
        "voice" => $voice,
        "volume" => $volume,
        "speech_rate" => $speech_rate,
        "pitch_rate" => $pitch_rate
    );
    $body = json_encode($taskArr);
    $results['task_array'] = $taskArr;
    $curl = curl_init();
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
    /**
     * 设置HTTPS POST URL。
     */
    curl_setopt($curl, CURLOPT_URL, $url);
    curl_setopt($curl, CURLOPT_POST, TRUE);
    /**
     * 设置HTTPS POST请求头部。
     * */
    $httpHeaders = array(
        "Content-Type: application/json"
    );
    curl_setopt($curl, CURLOPT_HTTPHEADER, $httpHeaders);
    /**
     * 设置HTTPS POST请求体。
     */
    curl_setopt($curl, CURLOPT_POSTFIELDS, $body);
    /**
     * 设置返回的响应包含HTTPS头部信息。
     */
    curl_setopt($curl, CURLOPT_HEADER, TRUE);
    /**
     * 发送HTTPS POST请求。
     */
    $response = curl_exec($curl);
    if ($response == FALSE) {
        $results['error'] = 1;
        $results['reason'] = '发送请求失败，请检查接口是否失效！';
        echo json_encode($results, JSON_UNESCAPED_UNICODE);
        curl_close($curl);
        return ;
    }
    /**
     * 处理服务端返回的响应。
     */
    $headerSize = curl_getinfo($curl, CURLINFO_HEADER_SIZE);
    $headers = substr($response, 0, $headerSize);
    $bodyContent = substr($response, $headerSize);
    curl_close($curl);

    $time = empty($_POST['time'])?time():$_POST['time'];
    $fileName = $_audioDir . getFileNameByMd5($time, $format);
    $fileUrl = $fileUrl . getFileNameByMd5($time, $format);
    if (stripos($headers, "Content-Type: audio/mpeg") != FALSE || stripos($headers, "Content-Type:audio/mpeg") != FALSE) {
        file_put_contents($fileName, $bodyContent);
        $results['time'] = $time;
        $results['error'] = 0;
        $results['audio_path'] = $fileName;
        $results['audio_url'] = $fileUrl;
        echo json_encode($results, JSON_UNESCAPED_UNICODE);
    }
    else {
        $results['time'] = $time;
        $results['error'] = 1;
        $results['reason'] = '发送请求失败，请检查接口是否失效！';
        echo json_encode($results, JSON_UNESCAPED_UNICODE);
    }
}

?>