#list module information
echo -e "lista as informações do modulo\n"
echo -e "$ modinfo misc.ko\n"
modinfo misc.ko
echo -e "\n"
read -p "Continuar ... "
echo -e "----------------------------------------------"
#install the module

echo -e "instala o modulo\n"
echo -e "# insmod misc.ko\n"
insmod misc.ko
read -p "Continuar ... "
echo -e "----------------------------------------------"


# check if there is the node on /dev 
echo -e "Valida se o nó de dispositivo em /dev/Erico existe"
if [[ $(find /dev -name Erico) != "" ]]; then
	echo -e "/dev/Erico foi criado pelo udev\n"
fi;
echo -e "$ ls -l /dev/Erico --color=auto\n"
ls -l /dev/Erico --color=auto
echo -e "\n"
read -p "Continuar ... "
echo -e "----------------------------------------------"



# read from /dev/Erico 
echo -e "lê 5x a partir de /dev/Erico\n"
echo "# for i in {1..5}; do cat /dev/Erico; echo -e \"\\n\"; done;"
echo -e "\n"
for i in {1..5}; do
	cat /dev/Erico
	echo -e "\n"
done;
echo -e "\n"
read -p "Continuar ... "
echo -e "----------------------------------------------"



# write once and read again from /dev/Erico 
echo -e "escreve uma vez e lê de novo 5x a partir de /dev/Erico\n"
echo -e "# echo \"exemplo Um de Infra de Soft feito por Erico\" > /dev/Erico\n"
echo "exemplo Um de Infra de Soft feito por Erico" > /dev/Erico

echo "# for i in {1..5}; do cat /dev/Erico; echo -e \"\\n\"; done;"
echo -e "\n"
for i in {1..5}; do
	cat /dev/Erico
	echo -e "\n"
done;
echo -e "\n"
read -p "Continuar ... "
echo -e "----------------------------------------------"



#remove the module 
echo -e "remove o module\n"
echo -e "# rmmod misc.ko\n"
rmmod misc.ko
read -p "Continuar ... "
echo -e "----------------------------------------------"


# message on dmesg
echo -e "mensagem no dmesg (display messages)\n"
echo -e "dmesg | tail\n"
dmesg | tail
echo -e "----------------------------------------------"

