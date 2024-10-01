#include <stdio.h>  //biblioteca padrão de entrada e saída.
#include <string.h> //biblioteca padrão de manipulação de strings.


//struct Produto (armazena os dados de um produto, incluindo código, nome e preço):
typedef struct { 
    int codigo;     //variável do código do produto.
    char nome[30];  //nome do produto (com até 30 caracteres).
    float preco;    //variável do preco do produto.
} Produto;


//struct Carrinho: (armazena os produtos selecionados e a quantidade de cada produto):
typedef struct {
    Produto produto;
    int quantidade;  //variável da quantidade de produtos.
} Carrinho;          


Produto produtos[50];   //array estático de Produto para armazenar até 50 produtos.
Carrinho carrinho[50];  //array estático de Carrinho para armazenar até 50 produtos diferentes no carrinho.
int totalProdutos = 0;  //variável que armazena o número total de produtos cadastrados.
int totalCarrinho = 0;  //variável que armazena o número total de produtos no carrinho.

//função auxiliar para exibir as informações de um produto:
void infoProduto(Produto prod) {

    //exibção do código, nome e preço do produto:
    printf("\nCodigo: %d  \nNome: %s \nPreco: R$%.2f\n", prod.codigo, prod.nome, prod.preco);
}

//função que permite o cadastro de novos produtos:
void cadastrarProduto() {
    if (totalProdutos < 50) {  //verifica se ainda tem espaço para cadastrar mais produtos (o máximo é 50).
        Produto prod;          //cria uma variável para armazenar os dados do novo produto.
        printf("\n---------------------------------------------\n");
        printf("\nCadastrar Produto:");
        printf("\nDigite o codigo do produto: ");
        scanf("%d", &prod.codigo);      //recebe o código do produto.
        printf("Digite o nome do produto: ");
        scanf("%s", prod.nome);         //recebe o nome do produto.
        printf("Digite o preco do produto: ");
        scanf("%f", &prod.preco);       //recebe o preço do produto.

        produtos[totalProdutos] = prod; //armazena o produto no array de produtos.
        totalProdutos++;                //incrementa o contador de produtos cadastrados.
        printf("\nProduto cadastrado com sucesso!\n");

    } else {
        printf("\nLimite de produtos cadastrados atingido.\n"); //informa que não pode cadastrar mais produtos.
    }
}

//função que lista/exibe os produtos cadastrados:
void listarProdutos() {
    if (totalProdutos == 0) {  //verifica se tem produtos cadastrados.
        printf("\nNenhum produto cadastrado.\n");
    } else {
        printf("\n---------------------------------------------\n");
        printf("\nLista de produtos disponiveis:\n");
        for (int i = 0; i < totalProdutos; i++) {  //mostra sobre todos os produtos cadastrados.
            infoProduto(produtos[i]);              //exibe as informações de cada produto.
        }
    }
}

//função que verifica se o produto já está no carrinho:
int temNoCarrinho(int codigo) {
    for (int i = 0; i < totalCarrinho; i++) {        //mostra sobre os produtos no carrinho.
        if (carrinho[i].produto.codigo == codigo) {  //verifica se o código do produto já está no carrinho.
            return i;  //retorna o indice do produto no carrinho.
        }
    }
    return -1;  //retorna -1 se o produto não for encontrado no carrinho.
}

//função que retorna um produto a partir do código informado:
Produto pegarProdutoPorCodigo(int codigo) {
    for (int i = 0; i < totalProdutos; i++) {      //mostra sobre todos os produtos cadastrados.
        if (produtos[i].codigo == codigo) {        //verifica se o código do produto corresponde ao produto.
            return produtos[i];  //retorna o produto encontrado.
        }
    }

    //caso o produto não for encontrado, retornará um produto inválido com código -1:
    Produto produtoInvalido = { -1, "", 0.0 };
    return produtoInvalido;
}

//função que adiciona produtos ao carrinho:
void comprarProduto() {
    int codigo, quantidade;  //variável do código e da quantidade do produto.
    printf("\n---------------------------------------------\n");
    printf("\nComprar Produto:\n");
    printf("Digite o codigo do produto que deseja comprar: ");
    scanf("%d", &codigo);   //recebe o código do produto que será comprado.

    //verifica se o produto está cadastrado:
    Produto produto = pegarProdutoPorCodigo(codigo);

    if (produto.codigo != -1) {  //se o produto for válido/encontrado...
        printf("Digite a quantidade: ");
        scanf("%d", &quantidade);  //recebe a quantidade que será comprada.

        //verifica se o produto já está no carrinho:
        int indiceCarrinho = temNoCarrinho(codigo);
        if (indiceCarrinho == -1) {  //se o produto não estiver no carrinho...
            carrinho[totalCarrinho].produto = produto;    //adiciona o produto ao carrinho;
            carrinho[totalCarrinho].quantidade = quantidade; //define a quantidade comprada;
            totalCarrinho++;  //incrementa o contador do carrinho;
        } else {
            carrinho[indiceCarrinho].quantidade += quantidade; //atualiza a quantidade se o produto já estiver no carrinho.
        }
        printf("\nProduto adicionado ao carrinho.\n");
    } else {
        printf("\nProduto nao encontrado.\n");  //mensagem caso o produto não seja encontrado.
    }
}

//função que visualiza/exibe os produtos no carrinho:
void visualizarCarrinho() {
    if (totalCarrinho == 0) {  //verifica se tem produtos no carrinho.
        printf("\nO carrinho esta vazio.");
    } else {
        printf("\n---------------------------------------------\n");
        printf("\nCarrinho de compras:\n");
        for (int i = 0; i < totalCarrinho; i++) {  //mostra sobre os produtos no carrinho.
            printf("\nCodigo: %d \nProduto: %s \nQuantidade: %d \nPreco unitario: R$%.2f \nTotal: R$%.2f\n",
                   carrinho[i].produto.codigo,
                   carrinho[i].produto.nome, 
                   carrinho[i].quantidade,
                   carrinho[i].produto.preco,
                   carrinho[i].quantidade * carrinho[i].produto.preco);  //mostra os detalhes do produto e o subtotal.
        }
    }
}

//função que remove um produto do carrinho:
void removerProdutoDoCarrinho() {
    if (totalCarrinho == 0) {  //verifica se tem produtos no carrinho.
        printf("\nO carrinho esta vazio, nada a ser removido.\n");
        return;
    }

    int codigo;
    printf("\n-----------------------------------------------------------------\n");
    printf("Digite o codigo do produto que deseja remover do carrinho: ");
    scanf("%d", &codigo);  //recebe o código do produto que será removido.

    int indiceCarrinho = temNoCarrinho(codigo);  //verifica se o produto está no carrinho.
    if (indiceCarrinho != -1) {  //se o produto for encontrado no carrinho...

        //remove o produto deslocando os elementos seguintes para preencher o espaço vazio:
        for (int i = indiceCarrinho; i < totalCarrinho - 1; i++) {
            carrinho[i] = carrinho[i + 1];  //move os produtos no array.
        }
        totalCarrinho--;  //decrementa o contador de produtos no carrinho.
        printf("\nProduto removido do carrinho com sucesso.\n");
    } else {
        printf("\nProduto nao encontrado no carrinho.\n");  //mensagem caso o produto não esteja no carrinho.
    }
}

//função que calcula, exibe o valor total da compra e esvazia o carrinho; finaliza o pedido e limpa o carrinho:
void fecharPedido() {
    if (totalCarrinho == 0) {  //verifica se tem produtos no carrinho.
        printf("\nO carrinho esta vazio.\n");
    } else {
        float total = 0;  //variável para armazenar o valor total da compra.
        printf("\n---------------------------------------------\n");
        printf("\nFechar Pedido\n");
        printf("\nFatura:\n");
        for (int i = 0; i < totalCarrinho; i++) {  //mostra sobre os produtos no carrinho.
            float subtotal = carrinho[i].quantidade * carrinho[i].produto.preco;  //cálculo do subtotal.
            printf("\nCodigo: %d \nProduto: %s \nPreco unitario: R$%.2f \nQuantidade: %d \nTotal: R$%.2f\n",
                   carrinho[i].produto.codigo, 
                   carrinho[i].produto.nome, 
                   carrinho[i].produto.preco,
                   carrinho[i].quantidade, 
                   subtotal);  //exibe os detalhes do produto e o subtotal.
            total += subtotal;  //soma do valor total final.
        }
        printf("Valor total da compra: R$%.2f\n", total);  //exibe o valor total da compra.

        totalCarrinho = 0;  //esvazia o carrinho após finalizar o pedido.
        printf("\nCompra finalizada com sucesso! O carrinho foi esvaziado.\n");
    }
}

//função que exibe o menu principal e gerenciar as opções do usuário; gerencia o fluxo do programa e as opções do usuário:
void menu() {
    int opcao;
    do {
        printf("\n---------------------------------------------\n");
        printf("\nMENU:\n");
        printf("1. Cadastrar Produto\n"); //opção de cadastrar o produto.
        printf("2. Listar Produtos\n");   //opção de listar os produtos cadastrados.
        printf("3. Comprar Produto\n");   //opção de comprar o produto (adicioná-lo ao carrinho).
        printf("4. Visualizar Carrinho\n"); //opção de visualizar os produtos no carrinho.
        printf("5. Remover produto do carrinho\n"); //opção de remover produtos do carrinho.
        printf("6. Fechar Pedido\n"); //opção de finalizar o pedido.
        printf("7. Sair\n"); //opção para sair do sistema.
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);  //eecebe a opção escolhida pelo usuário.

        //chama a função correspondente à opção escolhida pelo usuário:
        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                listarProdutos();
                break;
            case 3:
                comprarProduto();
                break;
            case 4:
                visualizarCarrinho();
                break;
            case 5:
                removerProdutoDoCarrinho();
                break;
            case 6:
                fecharPedido();
                break;
            case 7:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpcao invalida.\n");
                break;
        }
    } while (opcao != 7);  //loop que repete o menu até o usuário escolher a opção de sair.
}

//função principal do programa:
int main() {
    menu();  //chama a função que exibe o menu.
    return 0; //finalização do programa.
}
