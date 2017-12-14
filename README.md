# ZIP_CODE_search

ZIP_CODE_search

Neste repositório há 3 pastas, 'archive_reader', 'searcher' e 'zipcodes_arhives', cada um com sua importância. 

Na pasta 'zipcodes_arhives' há todos os códigos postais para a execução da busca, todos os arquivos(exceto one_archive.txt) foram obtidos no www.geonames.org/.

Na pasta 'archive_reader' há um código que lê todos os arquivos da pasta zipcodes_arhives, ordena de forma que facilite a criação da tabela hash e salva como um novo arquivo na pasta 'zipcodes_arhives' com o nome de 'one_archive.txt'. 
A ordenação feita em 'archive_reader' faz uso do algoritmo de quick sort para uma ordenação parcial da que se deseja.

E na pasta 'searcher' há o código que lê o arquivo 'one_archive.txt' e quando executado faz algumas perguntas para que o usuário entre com o nome da cidade a ser buscada e com o país especifíco, caso queira fazer a busca em todos os países use a ultima opção.
A implementação de 'searcher' faz uso de uma tabela hash, podendo ser considerada uma matriz hash por ser um vetor bidimensional de hash. O objetivo do uso é melhorar o tempo de busca em uma lista encadeada em que nesse software há mais de um milhão de elementos.
As chaves para a matriz hash são a primeira letra da cidade a ser pesquisada e o país a ser pesquisado, porém pode ser omitido.

Utilizando o '#define DEBUG_TIME' mostra o tempo de execução de algumas etapas dos códigos, como a leitura do arquivo, tempo de execução do quick sort(archive_reader) e tempo das buscas com e sem o uso da tabela hash(searcher).
DEBUG_TIME está implementado de forma multi-plataforma Windows e Linux.
Pode ser observado que o uso da matriz hash chega a proporcionar até um tempo de busca três vezes menor do que a busca pela lista inteira.

Melhorias a serem feitas: 
-Traduzir todos os documentos para inglês com intuíto de deixar mais universal, 
-Adicionar comentários para melhor compreesão, 
-Melhorar a forma da estrutura em que é feita a tabela hash
-Talvez melhorar a construção ou fazer uso de algum outro algoritmo de implementação da tabela hash com intuíto de otimizar o tempo de busca ainda mais.
