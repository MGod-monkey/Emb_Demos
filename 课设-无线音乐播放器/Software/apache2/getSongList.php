<?php
/*
 * @Author: your name
 * @Date: 2021-08-29 20:31:11
 * @LastEditTime: 2021-08-29 22:05:20
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \undefinedc:\Users\17814\Desktop\getSongList.php
 */

header('Content-Type:application/json');

$music_dir = '/var/www/html/music';

try{	
	//$ip = 'http://' . $_SERVER["REMOTE_ADDR"] . '/';	//获取内网IP地址
	$externalContent = file_get_contents('http://checkip.dyndns.com/');	//获取公网IP地址
	preg_match('/Current IP Address: \[?([:.0-9a-fA-F]+)\]?/', $externalContent, $m);
	$ip = 'http://' . $m[1] . '/';
	
	$handler = opendir($music_dir);
	$result = array('error' => 0, 'reason' => '', 'num' => 0, 'songs' => array());

	while (($filename = readdir($handler)) !== false) {
		if($filename != "." && $filename != "..") {
			$_filename = str_replace(' ', '', $filename);	//去空格
			// $result['reason1'] = chmod($music_dir . '/' . $filename, 0766);	//修改文件权限，否则会出现修改不了文件名
			rename($music_dir . '/' . $filename, $music_dir . '/' . $_filename);		//改文件名
			$filename = $ip . 'music/' . $_filename;
			array_push($result['songs'], $filename);
		}
	}
	closedir($handler);
	$result['num'] = count($result['songs']);
	echo json_encode($result, JSON_UNESCAPED_UNICODE);
} catch (Exception $e){
	$result['error'] = 1;
	$result['reason'] = $e.getMessage();
}
?>
