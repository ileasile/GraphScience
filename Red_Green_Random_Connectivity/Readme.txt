Формат входного файла следующий:
5 6 // |V|, |E|
1 5 // start, finish
R // initial state (R=Red, G=Green)
0.2 // probability of state changing
// Описание дуг в формате <from>, <to>, <color>
// <color> = {R=Red, G=Green, B=Black}
1 2 R 
2 3 B
2 4 G
3 4 R
3 5 R
4 5 R