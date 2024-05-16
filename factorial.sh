: '

Problem :- Write a shell script to find factorial of a given number
'
#shell script for factorial of a number
#factorial using while loop
echo "Enter a number:-"
read num
fact=1
while [ $num -gt 1 ]
do
  fact=$((fact * num))
  num=$((num - 1))
done
echo $fact
: '
kkw@kkw-HP-280-G2-MT-Legacy:~/Desktop$ chmod +x os_p2.sh
kkw@kkw-HP-280-G2-MT-Legacy:~/Desktop$ ./os_p2.sh
Enter a number:- 50
-3258495067890909184
'