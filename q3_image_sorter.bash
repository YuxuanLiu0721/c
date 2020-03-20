#!/bin/bash

name=$(echo $1 | sed 's/\//_/g')
convert  `ls -ltr -R $1/*/*.jpg|grep -o '[^ ]*\.jpg'` -append  $name.jpg
