#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define FILENAME "usuarios.txt"
#define SHIFT 3  


typedef struct {
    int id;
    char nome[MAX_NAME_LEN];
} Usuario;


void cifraDeCesar(char *texto) {
    int i;
    for (i = 0; texto[i] != '\0'; i++) {
        texto[i] += SHIFT;
    }
}


void descifraDeCesar(char *texto) {
    int i;
    for (i = 0; texto[i] != '\0'; i++) {
        texto[i] -= SHIFT;
    }
}


void incluirUsuario() {
    Usuario usuario;
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o ID do usuario: ");
    scanf("%d", &usuario.id);
    printf("Digite o nome do usuario: ");
    scanf("%s", usuario.nome);

    
    cifraDeCesar(usuario.nome);

    
    fprintf(file, "%d %s\n", usuario.id, usuario.nome);
    fclose(file);

    printf("Usuario incluído com sucesso!\n");
}


void listarUsuarios() {
    Usuario usuario;
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Nenhum usuario encontrado.\n");
        return;
    }

    printf("Lista de usuarios:\n");
    while (fscanf(file, "%d %s", &usuario.id, usuario.nome) != EOF) {
        descifraDeCesar(usuario.nome);
        printf("ID: %d, Nome: %s\n", usuario.id, usuario.nome);
    }
    fclose(file);
}


void removerDuplicados() {
    Usuario usuarios[100];  
    int totalUsuarios = 0;
    Usuario usuarioAtual;
    FILE *file = fopen(FILENAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    
    if (file == NULL || tempFile == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    
    while (fscanf(file, "%d %s", &usuarioAtual.id, usuarioAtual.nome) != EOF) {
        descifraDeCesar(usuarioAtual.nome);

        
        int duplicado = 0;
        int i;
		for ( i = 0; i < totalUsuarios; i++) {
            if (usuarios[i].id == usuarioAtual.id) {
                printf("ID duplicado encontrado e removido: ID %d\n", usuarioAtual.id);
                duplicado = 1;
                break;
            }
        }

        
        if (!duplicado) {
            usuarios[totalUsuarios++] = usuarioAtual;
            cifraDeCesar(usuarioAtual.nome); 
            fprintf(tempFile, "%d %s\n", usuarioAtual.id, usuarioAtual.nome);
        }
    }

    fclose(file);
    fclose(tempFile);

    
    remove(FILENAME);
    rename("temp.txt", FILENAME);
}

void alterarUsuario() {
    Usuario usuario;
    int id, found = 0;
    FILE *file = fopen(FILENAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o ID do usuario que deseja alterar: ");
    scanf("%d", &id);

    while (fscanf(file, "%d %s", &usuario.id, usuario.nome) != EOF) {
        descifraDeCesar(usuario.nome);
        if (usuario.id == id) {
            found = 1;
            printf("Digite o novo nome do usuario: ");
            scanf("%s", usuario.nome);
            cifraDeCesar(usuario.nome);
        } else {
            cifraDeCesar(usuario.nome);
        }
        fprintf(tempFile, "%d %s\n", usuario.id, usuario.nome);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found) {
        printf("Usuario alterado com sucesso!\n");
    } else {
        printf("Usuario nao encontrado.\n");
    }
}


void excluirUsuario() {
    Usuario usuario;
    int id, found = 0;
    FILE *file = fopen(FILENAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o ID do usuario que deseja excluir: ");
    scanf("%d", &id);

    while (fscanf(file, "%d %s", &usuario.id, usuario.nome) != EOF) {
        descifraDeCesar(usuario.nome);
        if (usuario.id != id) {
            cifraDeCesar(usuario.nome);
            fprintf(tempFile, "%d %s\n", usuario.id, usuario.nome);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found) {
        printf("Usuario excluído com sucesso!\n");
    } else {
        printf("Usuario nao encontrado.\n");
    }
}

int main() {
    int opcao;

    
    removerDuplicados();

    do {
        printf("\nMenu:\n");
        printf("1. Incluir Usuario\n");
        printf("2. Alterar Usuario\n");
        printf("3. Excluir Usuario\n");
        printf("4. Listar Usuarios\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incluirUsuario();
                break;
            case 2:
                alterarUsuario();
                break;
            case 3:
                excluirUsuario();
                break;
            case 4:
                listarUsuarios();
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}

