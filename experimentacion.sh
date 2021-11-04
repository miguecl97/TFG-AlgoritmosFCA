#!/bin/bash


echo " Enter the value for parameter |g'| of datasets"
read n
if [ $n -eq 10 ];
then
for i in {400,450,500};do
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
done
for run in {1..10}; do
   ./bin/main 20 100 20 $run
	./bin/main 40 100 20 $run
   ./bin/main 60 100 20 $run
   ./bin/main 80 100 20 $run
   ./bin/main 100 100 20 $run
done
echo $run
elif [ $n -eq 30 ];
then
for i in {20,40,60,80,100};do
cp tablesheet.csv "results/M100/g'${n}/tables/table${i}.csv";
done
for run in {1..10}; do
   ./bin/main 20 100 30 $i
	./bin/main 40 100 30 $i
   ./bin/main 60 100 30 $i
   ./bin/main 80 100 30 $i
   ./bin/main 100 100 30 $i
done
echo $run
elif [ $n -eq 40 ];
then
for i in {20,40,60};do
cp tablesheet.csv "results/M100/g'${n}/tables/table${i}.csv";
for run in {1..10}; do
  ./bin/main $i 100 40 $run
done
done
echo $run
for i in {400,450,500};do
cp tablesheet.csv "results/M100/g'${n}/tables/table${i}.csv";
for run in {1..10}; do
   ./bin/main $i 100 10 $run
	echo $run
done
done
else
echo "Not in the range of experimentation; must be {10,20,30,40}"
fi

