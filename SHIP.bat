ECHO "_____________________________"
ECHO "| SHIP IO BATCH COMPILATION |"
ECHO "|___________________________|"
ECHO 
ECHO "_____________________________"
ECHO "| Compiling CLIENT Program  |"
ECHO "|___________________________|"
ECHO 

cd client
make ../SHIP_CLI

ECHO 
ECHO "_____________________________"
ECHO "| Compiling SERVER Program  |"
ECHO "|___________________________|"
ECHO 

cd ../server
make ../SHIP_SER

