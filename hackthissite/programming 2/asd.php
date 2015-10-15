<?php
$im = imagecreatefrompng("PNG.png");
list($width, $height, $type, $attr)= getimagesize("PNG.png");
$last = 0;
$ans = "";
for($i=0;$i<$height;$i++){
	for($j=0;$j<$width;$j++){
		$rgb = imagecolorat($im,$j,$i);
		if($rgb==1){
			if($i*100+$j-$last==45) $ans.="-";
			if($i*100+$j-$last==46) $ans.=".";
			if($i*100+$j-$last==32) $ans.=" ";
			$last =$i*100+$j;
		}
	}
}
echo $ans."\n";

?>