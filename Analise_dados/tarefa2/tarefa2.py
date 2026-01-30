import tarefa1

if __name__ == '__main__':
    itotal = 200
    m = 0.3

    specific_impulse = tarefa1.isp(itotal, m)
    
    print(tarefa1.vel_exaust(specific_impulse))