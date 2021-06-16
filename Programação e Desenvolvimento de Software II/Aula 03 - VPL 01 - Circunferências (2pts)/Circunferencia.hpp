struct Circunferencia {
    float xc;
    float yc;
    float raio;

    Circunferencia(float xc_, float yc_, float raio_){
        xc = xc_;
        yc = yc_;
        raio = raio_;

    }

    float calcularArea(){
        return 3.14*raio*raio;
    }

    bool possuiIntersecao(Circunferencia *a){
        float distC;
        float distR = raio+a->raio;
        distC = (xc-a->xc)+(yc-a->yc);
        if (distC < 0){
        distC=-distC;
        }

        if (distC > distR)
        {
            return false;
        }
        else
        {
            return true;
        }
        
    }

};