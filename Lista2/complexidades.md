# 2.1:

Dados:
inserção = 8n²
intercalação = 64nlogn

Buscar valor de n para:
8n² < 64n log n
n < 8 log n

Enquanto n aumenta, a diferença na eficiência entre esses algoritmos aumenta, e a ordenação por intercalação se prova como a escolha mais eficiente

# 2.2:

Para 100n² ser mais rápido que 2n:

100n² < 2n
50n² < n
50n < 1
n < 1/50

O menor valor de n para 100n² ser mais rápido que 2n = n < 1/50.

# 2.3:

Dizer que g(n) é O(f(n)) significa que f(n) domina assintoticamente g(n), ou seja, g(n) é da ordem no máximo f(n). Explicando em outras palavras, existe uma constante C que multiplicada por f(n) a partir de um número M, a função f(n) começará a dominar assintoticamente g(n) 

# 2.4:

Dizer que uma função g(n) é Ω(f(n)) significa que existe um C e um M, que g(n)>= C.f(n) para n >= M. Explicando em outras palavras, a partir de um número M, existe uma constante C que se multiplicar por f(n), a função especificará um limite inferior para g(n)

# 2.5:

Não faz sentido porque a notação O é usada para descrever um limite superior no tempo de execução de um algoritmo, não um limite inferior.

# 2.6:

Dados:
a(n) = n² - n + 500
b(n) = 47n + 47

Como a(n) o tempo de execução é quadrático, e  b(n) é polinomial, enquanto n aumenta, a diferença na eficiência entre esses algoritmos aumenta, e a ordenação por intercalação se prova como a escolha mais eficiente

# 2.7:

int i ,j ,k , s ; <!-- 1 -->
	for ( i =0; i < N -1; i ++) <!-- N -->
		for ( j = i +1; j < N ; j ++)<!-- (N - 1)(N / 2) = N²/2 - N -->
			for ( k =1; k < j ; k ++)<!-- j-1 -->
				s = 1;<!-- 1 -->

N * N²/2 - N * j-1 * 1 * 1 pode ser simplificado em N³ pois desconsidera complexidades não relevantes, ou seja, a complexidade do algoritmo é N³

# 2.8:

A complexidade de tempo e o desempenho do algoritmo depende do tamanho da entrada e independe da posição do valor máximo no array. O "maior" é O(n) no pior caso, Ω(n) no melhor caso e Θ(n) no caso médio.
