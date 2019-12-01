/*
 *
 *	 criado em /dev
 *
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>

#define DEVICE "Erico"
#define FISL_MESSAGE "Teste Driver de Erico"
#define BUFF_LEN 256
#define SUCCESS 0

static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);

/* ---------------------------------------------------------------- */

static int copied;
static char message[BUFF_LEN];


/*  
 * Tabela com as funções de manipulação de arquivos
 * Pode ser chamada de "jump table"
 * As funções declaradas aqui sobrescrevem as operações padrão.
 */

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

static struct miscdevice mdev = {
        .minor = MISC_DYNAMIC_MINOR,
        .name = DEVICE,
        .fops = &fops,
};

/* ---------------------------------------------------------------- */


static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
	int len;
	/*
	 * Se a mensagem já tiver sido copiada para o buffer,
	 * retorna 0 para indica EOF (fim do "arquivo")
	 */
	if(copied) return 0;

	/* 
	 * Copia a mensagem para o buffer que está no espaço 
	 * de memória do usuário
	 */	
	len = strnlen(message, BUFF_LEN);
	if(copy_to_user(buffer, message, len) == SUCCESS){
		copied++;
		printk(KERN_INFO "Mensagem lida");
		return len;
	} else {
		printk(KERN_ALERT "Erro ao ler mensagem");
		return -EIO; /* Erro de entrada e saida. I/O error. */

	}
}

static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
	// Reinicia para a mensagem original 


	if(copy_from_user(message, buff, len) == SUCCESS){    /* Copia um bloco de dados do espaço do usuário */
		printk(KERN_INFO "Conteudo escrito no disco virtual");
		return len;
	} else {
		printk(KERN_ALERT "Erro ao escrever no disco virtual");
		return -EIO;
	}

	//strncpy(message, FISL_MESSAGE, BUFF_LEN);
	//printk(KERN_INFO "Mensagem escrita");
	//return len;
}


static int device_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "arquivo aberto");
	/* Cada vez que o "arquivo" é aberto, inclui uma exclamação */
	copied = 0; 
	sprintf(message, "%s%s", message, "!");
	return 0; /* Success */
}

static int device_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "arquivo liberado");
	return 0;
}
/* ---------------------------------------------------------------- */



/* Função que será chamada quando o modulo é instalado */
static int __init inicia_module(void)
{

	strncpy(message, FISL_MESSAGE, BUFF_LEN); /* Realiza a cópia do conteúdo de uma variável a outra*/
	if(misc_register(&mdev) == SUCCESS)
		printk(KERN_INFO "Dispositivo registrado"); /* OK */
	else
		printk(KERN_ALERT "Erro ao registrar dispositivo"); /* Error */
	return 0;
}

/* Função que será chamada quando o modulo é removido  */
static void __exit finaliza_module(void)
{
	misc_deregister(&mdev);
	printk(KERN_INFO "Dispositivo removido\n");

}

/* ---------------------------------------------------------------- */

/* Registra quais funções devem ser chamadas para cada "evento"  */
module_init(inicia_module);
module_exit(finaliza_module);

/* Informações sobre o módulo  */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("");
MODULE_DESCRIPTION("Miscellaneous device module");