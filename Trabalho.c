#include <stdio.h>
#include <string.h>
#include <time.h>

//Definição do struct
struct PRODUTO {
  int cod;
  char nome[100];
  float preco;
  int quant;
};
//Leitura do struct
struct PRODUTO ler() {
  struct PRODUTO produto;
  scanf("%d %s %f %d" , &produto.cod , produto.nome , &produto.preco , &produto.quant);
  return produto;
}
//Busca no arquivo
struct PRODUTO busca(int codigo) {
  FILE *file = fopen("Estoque.txt" , "r");
  struct PRODUTO produto;
  int cod , quant;
  float preco;
  char nome[100];
  while(fscanf(file , "%d %s %f %d" , &cod , nome , &preco , &quant) != EOF) {
    if(cod == codigo) {
      produto.cod = cod;
      strcpy(produto.nome , nome);
      produto.preco = preco;
      produto.quant = quant;
    }
  }
  return produto;
  fclose(file);
}
//Registro no arquivo
void registrar(FILE *file , struct PRODUTO produto) {
  fprintf(file, "%d\t" , produto.cod);
  fprintf(file, "%s\t" , produto.nome);
  fprintf(file, "%.2f\t" , produto.preco);
  fprintf(file, "%d\n" , produto.quant);
}
//Vender produto
void vender(FILE *file , int cod1 , int quant1) {
  time_t tempoh;
  tempoh = time(NULL);
  FILE *arq = fopen("Nota Fiscal.txt" , "a");
  int cod2 , quant2;
  float preco , total = 0;
  char nome[100]; 
  while(fscanf(file , "%d %s %f %d" , &cod2 , nome , &preco , &quant2) != EOF) {
    if(cod1 == cod2) {
      total = (preco * quant1);
      fprintf(arq , "\n%s", ctime(&tempoh));
      fprintf(arq , "%d\t" , cod2);
      fprintf(arq , "%s\t" , nome);
      fprintf(arq , "%.2f\t" , preco);
      fprintf(arq , "%d\t" , quant1);
      fprintf(arq , "%.2f\n" , total);
    }
  }
  fclose(arq);
}
//Ver Nota Fiscal
void vendas(FILE *file) {
  char str[100];
  while(fscanf(file , "%s" , str) != EOF) {
    printf("%s\t" , str);
    printf("\n");
  }
}
//Verificar estoque
void verificar(FILE *file) {
  int cod , quant;
  char item[100];
  float preco;
  while(fscanf(file , "%d %s %f %d" , &cod , item , &preco , &quant) != EOF) {
    printf("%d\t%s\t%.2f\t%d\n" , cod , item , preco , quant);
  }
}
//Alterar item
void alterar(FILE *file , int codigo) {
  FILE *arq = fopen("tmp.txt" , "w");
  int cod1 , cod2 , quant1 , quant2;
  float preco1 , preco2;
  char nome1[100];
  char nome2[100];
  printf("Digite as novas informacoes\n");
  scanf("%d %s %f %d" , &cod2 , nome2 , &preco2 , &quant2);
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
  remove("Estoque.txt");
  rename("tmp.txt" , "Estoque.txt");
  fclose(arq);
}
//Excluir item do estoque
void apagar(FILE *file , int prod) {
  int quant , cod;
  char str[100];
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
  remove("Estoque.txt");
  rename("temp.txt" , "Estoque.txt");
  fclose(arq);
}
//Principal
int main() {
  FILE *file;
  int num , i;
  int cod , quant;
  printf("O que deseja fazer?\n");
  printf("\nRegistrar item - 1\nVender - 2\nVerificar estoque - 3\nItens vendidos - 4\nAlterar item - 5\nApagar item - 6\n");

  scanf("%d" , &num);
  if(num == 1) {
    int num2;
    file = fopen("Estoque.txt" , "a");
    printf("Quantos itens deseja registrar?\n");
    scanf("%d" , &num2);
    for(i = 0; i < num2; i++) {
      struct PRODUTO p = ler();
      struct PRODUTO prod = busca(p.cod);
      if(p.cod == prod.cod) {
        printf("Codigo ja existente!\n");
      }
      else {
        registrar(file , p);
      }
    }
  }
  else if(num == 2) {
    int num2;
    FILE *arq = fopen("Nota Fiscal.txt" , "a");
    for(i = 0; i < 1000; i++) {
      printf("Digite o codigo e a quantidade do produto:\n");
      file = fopen("Estoque.txt" , "r");
      scanf("%d %d" , &cod , &quant);
      vender(file , cod , quant);
      printf("Deseja continuar?\nSim - 1    Nao - 2\n");
      scanf("%d" , &num2);
      if(num2 == 2) {
        i = 1000;
      }
    }
    fprintf(arq , "\n");
    fclose(arq);
  }
  else if(num == 3) {
    file = fopen("Estoque.txt" , "r");
    verificar(file);
  }
  else if(num == 4) {
    file = fopen("Nota Fiscal.txt" , "r");
    vendas(file);
  }
  else if(num == 5) {
    file = fopen("Estoque.txt" , "r");
    printf("Digite o codigo do item a ser alterado:\n");
    int codigo;
    scanf("%d" , &codigo);
    alterar(file , codigo);
  }
  else if(num == 6) {
    printf("Digite o codigo do preduto a ser apagado:\n");
    int cod;
    scanf("%d" , &cod);
    file = fopen("Estoque.txt" , "r");
    apagar(file , cod);
  }
  fclose(file);
  return 0;
}
