ECHO SHIP IO BATCH COMPILATION
ECHO 

ECHO Compiling CLIENT Program
cd client
make ../SHIP_CLI

ECHO
ECHO Compiling SERVER Program
cd ../server
make ../SHIP_SER

