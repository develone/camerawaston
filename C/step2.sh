#!/bin/bash

 

i="0"
date
while [ $i -lt 10 ]
do
sudo ./step1.sh 
i=$[$i+1]
done
date
