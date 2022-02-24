import (
    std     "std.nlh"
    vmTutor "https://github.com/BoB1Edition/vmTutor"
)

func main() {
    Println("hello %s", "word");
    vmTutor.Test()
    int variable;
    for (int j=0; j<10; j++) {
        variable = NewVal(j)
    }
    Class cl(0.12)
    cl.Hello
}

func NewVal(int i) int {
    return i+i
}

class Class: std {
    int Value1
    func init()
    func init(float FL)
    bool check
    func Hello(string name) string
}

func Class::Hello(string name) string {
    Println("hello %s", name)
    return "file"
}