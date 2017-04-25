#!/bin/bash

files=( "$(ls silesia)" )

#mass encode

for i in {0..9};
do 
    for j in $files;
    do
        echo "PPM("$i"): silesia/"$j;
        #echo  ppm -Dorder $i -Dfile.in "silesia/"$j -Dfile.ppm "silesia/"$j$i".ppm";
        ant ppm -Dorder $i -Dfile.in "silesia/"$j -Dfile.ppm "silesia/"$j$i".ppm";
    done 
done

#mass decode

for i in {0..9};
do 
    for j in $files;
    do
        echo "UNPPM("$i"): silesia/"$j$i.ppm;
        #echo  unppm -Dorder $i -Dfile.ppm "silesia/"$j$i".ppm" -Dfile.out "silesia/"$j$i;
        ant unppm -Dorder $i -Dfile.ppm "silesia/"$j$i".ppm" -Dfile.out "silesia/"$j$i;
    done 
done


for i in {0..9};
do 
    for j in $files;
    do
        diff "silesia/"$j "silesia/"$j$i
    done 
done