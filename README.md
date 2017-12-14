# ZIP_CODE_search

ZIP_CODE_search

Neste repositório há 3 pastas, 'archive_reader', 'searcher' e 'zipcodes_arhives', cada um com sua importância. 

Na pasta 'zipcodes_arhives' há todos os códigos postais para a execução da busca, todos os arquivos(exceto one_archive.txt) foram obtidos no www.geonames.org/.

Na pasta 'archive_reader' há um código que lê todos os arquivos da pasta zipcodes_arhives, ordena de forma que facilite a criação da tabela hash e salva como um novo arquivo na pasta 'zipcodes_arhives' com o nome de 'one_archive.txt'. A ordenação feita também faz uso do algoritmo de quick sort.

E na pasta 'searcher' há o código que lê o arquivo 'one_archive.txt' e quando executado faz algumas perguntas para que o usuário entre com o nome da cidade a ser buscada e com o país especifíco, caso queira fazer a busca em todos os países use a ultima opção.

Utilizando o '#define DEBUG_TIME' mostra o tempo de execução de algumas etapas dos códigos, como a leitura do arquivo, tempo de execução do quick sort(archive_reader) e tempo das buscas com e sem o uso da tabela hash(searcher).
DEBUG_TIME está implementado de forma multi-plataforma Windows e Linux.

Melhorias a serem feitas: Traduzir todos os documentos para inglês com intuíto de deixar mais universal, adicionar comentários para melhor compreesão, melhorar a forma da estrutura em que é feita a tabela hash.
