# PG2021-1
Repositório contendo todas as listas de exercícios do Grau A e Grau B da disciplina de Processamento Gráfico de 2021.

## IMPORTANTE:
Repostas em extenso se encontram dentro da correspondente pasta por meio de um arquivo.txt, como é o caso do exercício 3 da Lista2.

Arquivo `dependecies`, que pode ser encontrado em https://github.com/fellowsheep/PG2021-1/tree/main/dependencies, foi alterado para a resolução dos exercícios, como mostra a seguir:
* Inclusão de arquivo `glad.c` - para não precisar repetir a inclusão do mesmo em cada projeto;
* Inclusão de arquivo `Shader.h` - para não precisar repetir a inclusão do mesmo em cada projeto;
* Inclusão de arquivo `Dependencies.txt` - não é necessário, usado somente como ajuda para vincular as dependências a cada projeto;
* Remoção de arquivos lib desnecessários da pasta GLFW - não é necessário removê-los, caso já tenho a pasta baixada.

Para atualizar a pasta `dependencies`, só é necessário incluir os dois primeiros arquivos listados acima.

Além disso, é possível que a solução abra no modo de Debug `x64`, o certo é o `x86`, só precisa mudar o modo de Debug na barra de ferramentas superior do Visual Studio para x86.

### Programas necessários para compilar o projeto:
- Visual Studio 2019;

### Intruções para compilar as Listas:
- Fazer o download em zip do repositório;
- Ir até onde o arquivo foi baixado, clicar com o botão direito do mouse na pasta e depois selecionar `Extrair aqui` e então abrir `PG2021-1-main`;
- Dentro da pasta PG2021-1-main estará as Listas, escolher uma Lista para ser aberta;
- Dentro das pastas `Lista` estará as correspondentes soluções das Listas, só precisa abrir a solução da Lista escolhida no Visual Studio 2019 (Ex.: Lista1.sln);
- Verificar o modo de Debug da solução, este deve estar em x86 na barra de feramentas superior do Visual Studio. Caso não esteja, deverá ser mudado para x86;
- Após a solução estar aberta, deve-se selecionar um projeto dentro da Lista para executar (Ex.: Exercício1), cada um corresponde a um exercício;
- No gerenciador de soluções do Visual Studios, clique com o botão direito do mouse em cima de um dos exercícios (Ex.: Exercício1), e selecione `Depurar` e depois `Iniciar Nova Instância`.

### Problemas na execução:
* Caso apareça algum erro de shader, modifique o número versão do core na primeira linha dos arquivos `transformation.fs` e `transformation.vs`, para uma inferior, exemplo: `#version 400 core`, ou menor;
* Caso tenha problema com as dependências, logo depois ao abrir o projeto no VS, faça a configuração do diretório das dependencias em:

Propriedades > C/C++ > Geral > Diretórios de Inclusão Adicionais > ... Adiciocione os diretórios `/glm`, `/GLAD/include` e `/GLFW/include` da pasta `/dependencies` deste projeto, como mostra a imagem a seguir;

![C-Geral](readme_images/C-Geral.png)

Propriedades > Vinculador > Geral > Diretórios de Biblioteca Adicionais > ... Adiciocione o diretório `GLFW/lib` da pasta `/dependencies` deste projeto, como mostra a imagem a seguir;

![Vinculador-Geral](readme_images/Vinculador-Geral.png)

Propriedades > Vinculador > Entrada > Dependências Adicionais > ... Adicione as bibliotecas `glfw3.lib` e `opengl32.lib`, como mostra a imagem a seguir.

![Vinculador-Entrada](readme_images/Vinculador-Entrada.png)

### Informações sobre o código:
Código usado é C++ juntamente com o OpenGL e GLSL, e as bibliotecas adicionais GLAD, GLFW e GLM.

OBS: Alguns exercícios eram particionados em partes (Ex.: 1.a, 1.b, 1.c) e foram feitos em um projeto só;
Outros exercícios foram feitos junto com outros e colocados em um projeto só, eles aparecem como no exemplo a seguir: `Exercício1-3` - resposta dos exercício de número 1 a 3.

* `Lista1:`
  - Projetos "Exercício1" ao "Exercício5" foram utilizados como base do código uma adaptação de https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.1.hello_triangle/hello_triangle.cpp;
  - Projetos "Exercício6" e "Exercício7" foram utilizados como base o código do learnopengl acima adaptado por Rossana Baptista Queiroz, que se encontra em https://github.com/fellowsheep/PG2021-1/blob/main/HelloTriangle/HelloTriangle/Source.cpp.
* `Lista2:`
  - Projetos "Exercício1-3" e "Exercício4-5" foram utilizados como base o código do learnopengl mais acima adaptado por Rossana Baptista Queiroz, que se encontra em https://github.com/fellowsheep/PG2021-1/blob/main/CameraOrtho/CameraOrtho/Source.cpp.
* `Lista3:`
  - Projetos "Exercício1" e "Exercício2" mesma coisa dos projetos da Lista2.
* `Lista5:`
  - Projeto "Exercício1-2" foi baseado no código adaptado do learnopengl por Rossana Baptista Queiroz, que pode ser encontrado em https://github.com/fellowsheep/PG2021-1/tree/main/Framework-PG/Framework-PG.
  - Exercício G (Vignette) foi baseado no tutorial de shader feito por Matt DesLauriers, encontrado em https://github.com/mattdesl/lwjgl-basics/wiki/ShaderLesson3.
  - Após rodar a solução da Lista5, irá aparecer todos os filtros de uma vez, dividos por linha:
    - Linha 1: Exercício A;
    - Linha 2: Exercício B, C, D;
    - Linha 3: Exercício E, F, G.
