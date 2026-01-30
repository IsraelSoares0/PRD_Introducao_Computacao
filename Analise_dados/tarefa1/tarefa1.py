def isp(impulso_total, massa_propelente):
    g = 9.8
    
    return impulso_total / (massa_propelente*g)

def vel_exaust(specific_impulse):
    g = 9.8
    
    return g * specific_impulse

if __name__ == '__main__':
    itotal = 200
    m = 0.3

    specific_impulse = isp(itotal, m)
    
    print(vel_exaust(specific_impulse))
