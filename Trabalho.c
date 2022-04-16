#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX 50

//Definição do struct
typedef struct PRODUTO {
  int cod;
  char nome[MAX];
  float preco;
  int quant;
} Produto;

//Leitura do struct
struct PRODUTO ler() {
  Produto p;
  printf("Digite o codigo do produto: ");
  scanf("%d" , &p.cod);

  printf("Digite o nome do produto: ");
  scanf("%s" , p.nome);

  printf("Digite o preco do produto: ");
  scanf("%f" , &p.preco);

  printf("Digite a quantidade disponivel do produto: ");
  scanf("%d" , &p.quant);

  return p;
}

//Busca no arquivo
struct PRODUTO busca(int codigo) {
  FILE *file = fopen("Estoque.txt" , "r");

  struct PRODUTO produto;
  int cod , quant;
  float preco;
  char nome[MAX];

  while(fscanf(file , "%d %s %f %d" , &cod , nome , &preco , &quant) != EOF) {
    if(cod == codigo) {
      produto.cod = cod;
      strcpy(produto.nome , nome);
      produto.preco = preco;
      produto.quant = quant;
    }
  }

  fclose(file);
  return produto;
}

// Verificar se um produto existe
int verificar (int codigo) {
  FILE *file = fopen("Estoque.txt" , "r");

  Produto p;
  int cod , quant;
  float preco;
  char nome[MAX];

  int result = 0

  while(fscanf(file , "%d %s %f %d" , &cod , nome , &preco , &quant) != EOF) {
    if(cod == codigo){
      result = 1
    }
  }

  fclose(file);
  return result;
}

//Registro no arquivo
void registrar(FILE *file , struct PRODUTO produto) {
  fprintf(file, "%d\t" , produto.cod);
  fprintf(file, "%s\t" , produto.nome);
  fprintf(file, "%.2f\t" , produto.preco);
  fprintf(file, "%d\n" , produto.quant);
}

//Atualia o Estoque.txt depois de uma Venda
void atualizar(int codigo , int estoque) {
  FILE *arq = fopen("tmp.txt" , "a");
  FILE *file = fopen("Estoque.txt" , "r");

  int cod1 , quant1 , quant2;
  float preco1;
  char nome1[MAX];

  while(fscanf(file , "%d %s %f %d" , &cod1 , nome1 , &preco1 , &quant1) != EOF) {
    quant2 = (quant1 - estoque);

    if(codigo == cod1) {
      fprintf(arq , "%d\t" , cod1);
      fprintf(arq , "%s\t" , nome1);
      fprintf(arq , "%.2f\t" , preco1);
      fprintf(arq , "%d\n" , quant2);
    }
    else {
      fprintf(arq , "%d\t" , cod1);
      fprintf(arq , "%s\t" , nome1);
      fprintf(arq , "%.2f\t" , preco1);
      fprintf(arq , "%d\n" , quant1);
    }
  }
  
  remove("Estoque.txt");
  rename("tmp.txt" , "Estoque.txt");

  fclose(arq);
  fclose(file);
}

//Vender produto
void vender(FILE *file , int cod1 , int quant1) {
  time_t tempoh;
  tempoh = time(NULL);

  FILE *arq = fopen("NotaFiscal.txt" , "a");

  int cod2 , quant2;
  float preco , total = 0;
  char nome[MAX]; 

  while(fscanf(file , "%d %s %f %d" , &cod2 , nome , &preco , &quant2) != EOF) {
    if(cod1 == cod2) {
      total = (preco * quant1);
      fprintf(arq , "\n%s\n", ctime(&tempoh));
      fprintf(arq , "\t%d" , cod2);
      fprintf(arq , "\t%s" , nome);
      fprintf(arq , "\t%.2f" , preco);
      fprintf(arq , "\t%d" , quant1);
      fprintf(arq , "\t%.2f\n" , total);
      atualizar(cod1 , quant1);
    }
  }

  fclose(arq);
}

//Ver Nota Fiscal
void vendas(FILE *file) {
  int cod , quant;
  float preco;
  char str[MAX];
  
  while(fscanf(file , "%s" ,str) != EOF) {
    printf("\n\n%s\t" , str);
  }

  printf("\n");
}

//Verificar estoque
void verificar(FILE *file) {
  int cod , quant;
  char item[MAX];
  float preco;

  while(fscanf(file , "%d %s %f %d" , &cod , item , &preco , &quant) != EOF) {
    //Reformatação da apresentação do estoque
    printf("%d\t%s\t%.2f\t%d\n\n" , cod , item , preco , quant);
  }
}

//Alterar item
void alterar(FILE *file , int codigo) {
  FILE *arq = fopen("tmp.txt" , "w");

  int cod1 , cod2 , quant1 , quant2;
  float preco1 , preco2;
  char nome1[MAX];
  char nome2[MAX];

  printf("Digite o novo codigo: ");
  scanf("%d" , &cod2);

  printf("Digite o novo nome: ");
  scanf("%s" , nome2);

  printf("Digite o novo preco: ");
  scanf("%f" , &preco2);

  printf("Digite a quantidade disponivel: ");
  scanf("%d" , &quant2);
  
  while(fscanf(file , "%d %s %f %d" , &cod1 , nome1 , &preco1 , &quant1) != EOF) {
    if(codigo == cod1) {
      fprintf(arq , "%d\t" , cod2);
      fprintf(arq , "%s\t" , nome2);
      fprintf(arq , "%.2f\t" , preco2);
      fprintf(arq , "%d\n" , quant2);
    }
    else {
      fprintf(arq , "%d\t" , cod1);
      fprintf(arq , "%s\t" , nome1);
      fprintf(arq , "%.2f\t" , preco1);
      fprintf(arq , "%d\n" , quant1);
    }
  }

  fclose(arq);
  remove("Estoque.txt");
  rename("tmp.txt" , "Estoque.txt");
}

//Excluir item do estoque
void apagar(FILE *file , int prod) {
  int quant , cod;
  char str[MAX];
  float valor;

  FILE *arq = fopen("temp.txt" , "w");

  while(fscanf(file , "%d %s %f %d" , &cod , str , &valor , &quant) != EOF) {
    if(cod == prod) {
      cod = 0;
      fprintf(arq , "%d\t" , cod);
      fprintf(arq , "%s\t" , str);
      fprintf(arq , "%.2f\t" , valor);
      fprintf(arq , "%d\n" , quant);
    }
    else {
      fprintf(arq , "%d\t" , cod);
      fprintf(arq , "%s\t" , str);
      fprintf(arq , "%.2f\t" , valor);
      fprintf(arq , "%d\n" , quant);
    }
  }

  fclose(arq);
  remove("Estoque.txt");
  rename("temp.txt" , "Estoque.txt");
}

//Principal
int main() {
  FILE *file;
  int opcao;

  int cod , quant;
  float preco;
  char nome[MAX];

  Produto prod;

  printf("\n\n");

  printf("\t**********************\n");
  printf("\t***** Bem-Vindo! *****\n");
  printf("\t**********************\n\n\n");

  printf("\tRegistrar Produto - 1\n");
  printf("\tVender - 2\n");
  printf("\tConsulta Nota Fiscal - 3\n");
  printf("\tConsultar Estoque - 4\n");
  printf("\tBuscar Produto No Estoque - 5\n");
  printf("\tAlterar Informacoes Do Produto - 6\n");
  printf("\tExcluir Item Do Estoque - 7\n");

  printf("\n\nDigite o numero da opcao desejada: ");
  scanf("%d" , &opcao);

  int aux = 0;
  int num;

  switch(opcao) {
    case 1:
      while(aux != 1) {
        file = fopen("Estoque.txt" , "a");
        prod = ler();
        if(verificar(prod.cod) == 1)
          printf("Codigo ja existente\n");
        else{
          registrar(file , prod);

          printf("\nDeseja registrar mais um item?\n\n");
          printf("SIM - 0\n");
          printf("NAO - 1\n\n");
          printf("Digite sua opcao: ");

          scanf("%d" , &num);
        }
        
        if(num == 1)
          aux = 1;
      }
      break;

    case 2:
      file = fopen("Estoque.txt" , "r");
      while(aux != 1) {
        printf("Entre com o codigo do produto: ");
        int item , numero;
        scanf("%d" , &item);

        printf("Informe a quantidave vendida do produto: ");
        scanf("%d" , &numero);

        vender(file , item , numero);

        printf("\nDeseja continuar?\n\n");
        printf("SIM - 0\n");
        printf("NAO - 1\n\n");
        printf("Digite sua opcao: ");
        scanf("%d" , &num);

        if(num == 1)
          aux = 1;
      }

      break;

    case 3:
      file = fopen("NotaFiscal.txt" , "r");
      vendas(file);
      break;

    case 4:
      file = fopen("Estoque.txt" , "r");
      verificar(file);
      break;

    case 5:
      printf("Digite o codigo do produto procurado: ");
      scanf("%d" , &cod);

      busca(cod);
      break;

    case 6:
      file = fopen("Estoque.txt" , "r");
      printf("Digite o codigo do produto que sera alterado: ");
      scanf("%d" , &cod);

      alterar(file , cod);
      break;

    case 7:
      file = fopen("Estoque.txt" , "r");
      printf("Digite o codigo do produto que sera apagado: ");
      scanf("%d" , &cod);

      apagar(file , cod);
      break;

    default:
      printf("Opcao invalida!\n");
  }
  
  fclose(file);
  return 0;
}
