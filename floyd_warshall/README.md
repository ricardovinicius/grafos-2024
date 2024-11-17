Para gerar os casos de teste criei um script "generate_test_cases.py" que cria grafos direcionados com peso aleatórios, com tamanho razoável.
E para testar as soluções utilizei o método 'floyd_warshall' no script "generate_solutions.py" da biblioteca de python SciPy, que é amplamente testada e utilizada, como parâmetro de comparação.
O resultado de comparação com a minha implementação é positiva, e pode ser observada através do "fw_test.sh".
