# Projeto-Final-APA

## Descricao do problema
Uma transportadora chamada Entrega Tudo entrou em contato com o seu grupo a fim de negociar uma
consultoria. Essa empresa opera em toda a Paraiba e realiza um alto volume de entregas de produtos de
grandes empresas do setor de e-commerce, como a Amazonia S.A. e Magazine Maria. Em uma primeira
reuniao, lhes foi explicado que a Entrega Tudo recebe diariamente demandas de diversas empresas e
deve se planejar para realizar todas as entregas dentro do prazo estipulado. Visando elevar o nivel de
qualidade de servico, todas as entregas devem ser relizadas no dia seguinte ao recebimento da demanda.
Sendo assim, apesar de possuirem uma frota propria de veiculos, existe a possibilidade de terceirizar parte
das entregas para transportadoras menores de forma a garantir que toda a demanda sera satisfeita.
Atualmente, as rotas de entrega sao criadas manualmente por um funcionario da empresa. Entretanto,
devido ao rapido crescimento no volume de entregas, essa tarefa esta ficando cada vez mais complexa e
custosa. Sendo assim, a Entrega Tudo gostaria que voces desenvolvessem um algoritmo capaz de gerar
um plano de roteamento otimizado que vise reduzir ao m´aximo os custos para a empresa.
Apos a reuniao, seu grupo se juntou para elaborar um esboco do projeto e formalizar o problema de
otimizacao, de forma a descrever claramente todos os requisitos e objetivos. Voces chegaram a conclusao
que, diariamente, a empresa deve resolver o seguinte problema:

### Problema

“ Seja G = (V, A) um grafo orientado onde, V = {0, 1, . . . , n} e o conjunto de vertices, o
vertice 0 representa o deposito, n e o numero de clientes a serem atendidos, e A e o conjunto
de arcos do grafo. Um arco (i, j) ∈ A representa o caminho que um veiculo deve percorrer
para ir do ponto i ao j, e o custo associado a tal arco e dado por cij . Cada cliente i possui
uma demanda di de pacotes a serem entregues. A empresa possui uma frota com k veiculos,
todos do mesmo modelo e com capacidade Q. Todos os veiculos devem iniciar e terminar suas
rotas no deposito, a capacidade maxima deve ser respeitada e cada veiculo utilizado incorre
em um custo r para a empresa. Visto que existe a opcao de terceirizar entregas, caso um
cliente i nao seja atendido por nenhum veiculo, deve ser pago um valor pi para que a entrega
seja realizada por outra empresa. A fim de garantir uma utilizacao minima de sua frota e
de seus funcionarios, a empresa estabelece que ao menos L entregas devem ser realizas sem
terceirizacao. O objetivo do problema e encontrar o conjunto de rotas que minimize a soma
do custo de roteamento (custo dos arcos), do custo associado a utilizacao dos veiculos e do
total pago com a terceirizacao de entregas. ”
