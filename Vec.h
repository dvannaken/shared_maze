#ifndef Vec_h
#define Vec_h

template <class T>
class Vec {
    T x;
    T y;
    
public:
    Vec (){
        x = 0;
        y = 0;
    }
    
    Vec (T x, T y){
        this->x = x;
        this->y = y;
    }
	
	Vec ( const Vec &vec ){
        this->x = vec.getX();
        this->y = vec.getY();
    }
    
    void add (Vec u){
        x += u.x;
        y += u.y;
    }
    
    T getX() const {
        return x;
    }
    
    T getY() const {
        return y;
    }
    
    void setX(T x) {
        this->x = x;
    }
    
    void setY(T y) {
        this->y = y;
    }
    
};

#endif