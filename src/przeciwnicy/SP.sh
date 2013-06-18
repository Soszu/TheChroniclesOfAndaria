#!/bin/bash
$pom
for index in  *.jpg ; do
	pom=${index%.jpg}
	sam2p  $pom.jpg  $pom.png
	rm $pom.jpg
done
