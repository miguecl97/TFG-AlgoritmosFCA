#!/bin/bash


echo " Enter the value for parameter |g'| of datasets"
read n
if [ $n -eq 10 ];
then
for i in {20,40,60,80,100};do
cp tablesheet.csv "results/M100/g'${n}/tables/table${i}.csv";
for run in {1..10}; do
   ./bin/main $i 100 10 $run
	echo $run
done
done
elif [ $n -eq 20 ];
then
for i in {20,40,60,80,100};do
cp tablesheet.csv "results/M100/g'${n}/tables/table${i}.csv";
for run in {1..10}; do
   ./bin/main $i 100 20 $run
	echo $run
done
done
elif [ $n -eq 30 ];
then
for i in {20,40,60,80,100};do
cp tablesheet.csv "results/M100/g'${n}/tables/table${i}.csv";
for run in {1..10}; do
   ./bin/main $i 100 30 $run
	echo $run
done
done
elif [ $n -eq 40 ];
then
cp tablesheet.csv "results/M100/g'${n}/tables/table100.csv";
for run in {1..10}; do
  ./bin/main 100 100 40 $run
	echo $run
done
else
echo "Not in the range of experimentation; must be {10,20,30,40}"
fi

