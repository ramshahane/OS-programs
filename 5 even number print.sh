# Print first 5 even numbers 
number=0 
count=0 
while [ $count -lt 5 ]; do      
# use -ne for not equal to for odd numbers 
if [ $((number % 2)) -eq 0 ]; then 
echo $number 
((count++)) 
fi 
((number++))