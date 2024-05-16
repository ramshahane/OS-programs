: '

Problem :- Write a shell script for implementation of control flow statements
'
# Control flow statements in shell script
#Initializing two variables 
a=20 
b=20 

if [ $a == $b ] 
then 
    #If they are equal then print this 
    echo "a is equal to b"
else
    #else print this 
    echo "a is not equal to b"
fi 

var="hello"

# Check if the var is equal to "hello"
if [ $var == "hello" ]; then
  echo "The variable is equal to hello!"
else
  echo "The variable is not equal to hello!"
fi

case $color in
    red)
        echo "You chose red."
        ;;
    green)
        echo "You chose green."
        ;;
    blue)
        echo "You chose blue."
        ;;
    *)
        echo "Invalid color."
        ;;
esac