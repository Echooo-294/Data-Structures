from random import randint
def rand_phone(): return '"'+''.join([str(randint(0,9)) for j in range(11)])+'"'
with open('data.h','w',encoding='utf8') as fo:
    N=400
    fo.write('char phones[{}][100]={{\n'.format(N))
    fo.write(',\n'.join([rand_phone() for i in range(N)]))
    fo.write('\n};')