#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;
#define max 1000

//物品的评级（枚举类型）
enum Grade{null,general,adult,child};


class item{
public:
    item(){};
    item(string i,string t,string a,Grade g):id(i),title(t),author(a),grade(g){}
    void print();
    string getId(){return id;}
    string getTitle(){return title;}
    string getAuthor(){return author;}
    Grade getGrade(){return grade;}
    void set_id(string i){id=i;}
    void set_title(string t){title=t;}
    void set_author(string a){author=a;}
    void set_grade(Grade g){grade=g;}
protected:
    string id;//编号
    string title;//标题
    string author;//作者
    Grade grade;//评级（未评级、一般、成人、儿童）
};

void item::print(){
    cout<<"id:"<<id<<endl<<"title:"<<title<<endl<<"author:"<<author<<endl<<"grade:";
    switch (grade) {
        case null:
            cout<<"未评级"<<endl;
            break;
        case general:
            cout<<"一般"<<endl;
            break;
        case adult:
            cout<<"成人"<<endl;
            break;
        case child:
            cout<<"儿童"<<endl;
            break;
        default:
            break;
    }
}

//图书
class book:public item{
public:
    book(){};
    book(string i,string t,string a,Grade g,string pu,string I,int pa):item(i, t, a, g),publisher(pu),ISBN(I),page(pa){}
    void subprint();
    void set_publisher(string p){publisher=p;}
    void set_ISBN(string I){ISBN=I;}
    void set_Page(int p){page=p;}
    string get_publisher(){return publisher;}
    string get_ISBN(){return ISBN;}
    int get_page(){return page;}
private:
    string publisher;//出版社
    string ISBN;//ISBN号
    int page;//页数
};

void book::subprint(){
    item::print();
    cout<<"publisher:"<<publisher<<endl<<"ISBN:"<<ISBN<<endl<<"page:"<<page<<endl<<endl;
}

//视频光盘
class cd:public item{
public:
    cd(){};
    cd(string i,string t,string a,Grade g,string p,int y,int time):item(i, t, a, g),producer(p),year(y),time(time){}
    void subprint();
    void set_producer(string p){producer=p;}
    void set_year(int y){year=y;}
    void set_time(int t){time=t;}
    string get_producer(){return producer;}
    int get_year(){return year;}
    int get_time(){return time;}
private:
    string producer;//出品者的名字
    int year;//出品年份
    int time;//视频时长(秒)
};

void cd::subprint(){
    item::print();
    cout<<"producer:"<<producer<<endl<<"year:"<<year<<endl<<"time:"<<time<<endl<<endl;
}


//图画
class drawing:public item{
public:
    drawing(){};
    drawing(string i,string t,string a,Grade g,string n,int l,int w):item(i, t, a, g),nationality(n),length(l),width(w){}
    void subprint();
    void set_nationality(string n){nationality=n;}
    void set_length(int l){length=l;}
    void set_width(int w){width=w;}
    string get_nationality(){return nationality;}
    int get_length(){return length;}
    int get_width(){return width;}
private:
    string nationality;//出品国籍
    int length;//作品的长（以厘米记，整数）
    int width;//作品的宽（以厘米记，整数）
};

void drawing::subprint(){
    item::print();
    cout<<"nationality:"<<nationality<<endl<<"length:"<<length<<endl<<"width:"<<width<<endl<<endl;
}

//物品仓库，用于存放/添加物品
class library{
public:
    //添加物品
    void add_book(book b);//添加一个book对象
    void add_cd(cd c);//添加一个cd对象
    void add_drawing(drawing d);//添加一个drawing对象
    int get_book_count(){return book_count;};//返回book数
    int get_cd_count(){return cd_count;};//返回cd数
    int get_drawing_count(){return drawing_count;};//返回drawing数
    book* get_books(){return books;};//返回数组books
    cd* get_cds(){return cds;};//返回数组books
    drawing* get_drawings(){return drawings;};//返回数组books
    int whether_id_repeat(string id);//判断id是否重复，重复返回1，反之返回0
    int does_title_exist(string title);//判断是否存在此标题，存在返回1，反之返回0
    int does_id_exist(string id);//判断是否存在此编号，存在返回1，反之返回0
    int check_category(int category);//判断是否存在此类，存在返回1，反之返回0
    int remove(int type,string id);//删除（第一个参数用于确定类型，第二个参数为编号）（成功返回1，否则返回0）
    void statistics();
    void save();//存盘
    void load();//读档
    void show();//显示物品库
private:
    //物品数量（max为上限值）
    static int book_count;
    static int cd_count;
    static int drawing_count;
    //数组，用于存储物品
    book books[max];
    cd cds[max];
    drawing drawings[max];
};
int library::book_count=0;
int library::cd_count=0;
int library::drawing_count=0;

void library::add_book(book b){
    if(book_count<max)books[book_count++]=b;
    else cout<<"库满，不能再添加新的数据。"<<endl;
}
void library::add_cd(cd c){
    if(cd_count<max)cds[cd_count++]=c;
    else cout<<"库满，不能再添加新的数据。"<<endl;
}
void library::add_drawing(drawing d){
    if(drawing_count<max)drawings[drawing_count++]=d;
    else cout<<"库满，不能再添加新的数据。"<<endl;
}
int library::whether_id_repeat(string id){
    for(int i=0;i<book_count;i++){
        if(id==books[i].getId())return 1;
    }
    for(int i=0;i<cd_count;i++){
        if(id==cds[i].getId())return 1;
    }
    for(int i=0;i<drawing_count;i++){
        if(id==drawings[i].getId())return 1;
    }
    return 0;
}

//接受一个title，如果存在，则打印该物所有信息并根据所属类别返回1、2、3，反之返回0
int library::does_title_exist(string title){
    int exist=0;
    for(int i=0;i<book_count;i++){
        if(title==books[i].getTitle()){
            books[i].subprint();
            exist=1;
        }
    }
    for(int i=0;i<cd_count;i++){
        if(title==cds[i].getTitle()){
            cds[i].subprint();
            exist=1;
        }
    }
    for(int i=0;i<drawing_count;i++){
        if(title==drawings[i].getTitle()){
            drawings[i].subprint();
            exist=1;
        }
    }
    if(exist)return 1;
    return 0;
}

//接受一个id，如果存在，则打印该物所有信息并根据所属类别返回1、2、3，反之返回0
int library::does_id_exist(string id){
    for(int i=0;i<book_count;i++){
        if(id==books[i].getId()){
            books[i].subprint();
            return 1;
        }
    }
    for(int i=0;i<cd_count;i++){
        if(id==cds[i].getId()){
            cds[i].subprint();
            return 2;
        }
    }
    for(int i=0;i<drawing_count;i++){
        if(id==drawings[i].getId()){
            drawings[i].subprint();
            return 3;
        }
    }
    return 0;
}
int library::check_category(int category){
    //根据编号是否为空进行判断
    switch (category) {
        case 1:
            for(int i=0;i<book_count;i++)books[i].subprint();
            return 1;
        case 2:
            for(int i=0;i<cd_count;i++)cds[i].subprint();
            return 1;
        case 3:
            for(int i=0;i<drawing_count;i++)drawings[i].subprint();
            return 1;
        default:
            cout<<"未知错误！"<<endl;
            break;
    }
    return 0;
}
void library::show(){
    for(int i=0;i<book_count;i++){
        if(books[i].getId()!=""){
            books[i].subprint();
        }
    }
    for(int i=0;i<cd_count;i++){
        if(cds[i].getId()!=""){
            cds[i].subprint();
        }
    }
    for(int i=0;i<drawing_count;i++){
        if(drawings[i].getId()!=""){
            drawings[i].subprint();
        }
    }
}

int library::remove(int type,string id){
    int success=0;
    if(type==1){
        int index=0;//标记位置
        for(int i=0;i<get_book_count();i++){
            if(id==get_books()[i].getId())index=i;
        }
        for(int i=index;i<get_book_count()-1;i++){
            get_books()[i]=get_books()[i+1];
        }
        book_count--;
        success=1;
    }
    if(type==2){
        int index=0;//标记位置
        for(int i=0;i<get_cd_count();i++){
            if(id==get_cds()[i].getId())index=i;
        }
        for(int i=index;i<get_cd_count()-1;i++){
            get_cds()[i]=get_cds()[i+1];
        }
        cd_count--;
        success=1;
    }
    if(type==3){
        int index=0;//标记位置
        for(int i=0;i<get_drawing_count();i++){
            if(id==get_drawings()[i].getId())index=i;
        }
        for(int i=index;i<get_drawing_count()-1;i++){
            get_drawings()[i]=get_drawings()[i+1];
        }
        drawing_count--;
        success=1;
    }
    //如果删除成功
    if(success==1)cout<<"删除成功！"<<endl;
    //如果success不为1，则表明发生未知错误
    else cout<<"发生未知错误！"<<endl;
    return 0;
}

void library::statistics(){
    cout<<"当前物品库中总物品数="<<get_book_count()+get_cd_count()+get_drawing_count()<<endl;
    cout<<"图书数:"<<get_book_count()<<"本；视频光盘数:"<<get_cd_count()<<"张；图画数:"<<get_drawing_count()<<"幅。"<<endl;
}

void library::save(){
    // 以写模式打开文件
    ofstream outfile;
    cout<<"请输入文件名（建议保存至data.txt）：";
    string name;
    cin>>name;
    outfile.open(name,ios::out);
    
    //文件第一行特殊声明，表示该文件为 媒体库存储文件，方便以后的读取
    outfile<<"<!DOCTYPE 媒体库存盘>"<<endl;
    //第2、3、4行分别写入book、cd、drawing的数目
    outfile<<get_book_count()<<endl;
    outfile<<get_cd_count()<<endl;
    outfile<<get_drawing_count()<<endl;
    
    //逐行存储book数据
    for(int i=0;i<get_book_count();i++){
        outfile<<get_books()[i].getId()<<endl;
        outfile<<get_books()[i].getTitle()<<endl;
        outfile<<get_books()[i].getAuthor()<<endl;
        outfile<<get_books()[i].getGrade()<<endl;
        outfile<<get_books()[i].get_publisher()<<endl;
        outfile<<get_books()[i].get_ISBN()<<endl;
        outfile<<get_books()[i].get_page()<<endl;
    }
    
    //逐行存储cd数据
    for(int i=0;i<get_cd_count();i++){
        outfile<<get_cds()[i].getId()<<endl;
        outfile<<get_cds()[i].getTitle()<<endl;
        outfile<<get_cds()[i].getAuthor()<<endl;
        outfile<<get_cds()[i].getGrade()<<endl;
        outfile<<get_cds()[i].get_producer()<<endl;
        outfile<<get_cds()[i].get_year()<<endl;
        outfile<<get_cds()[i].get_time()<<endl;
    }
    
    //逐行存储drawing数据
   for(int i=0;i<get_drawing_count();i++){
        outfile<<get_drawings()[i].getId()<<endl;
        outfile<<get_drawings()[i].getTitle()<<endl;
        outfile<<get_drawings()[i].getAuthor()<<endl;
        outfile<<get_drawings()[i].getGrade()<<endl;
        outfile<<get_drawings()[i].get_nationality()<<endl;
        outfile<<get_drawings()[i].get_length()<<endl;
        outfile<<get_drawings()[i].get_width()<<endl;
    }
    outfile.close();
    cout<<"存盘成功！文件存储于："<<name<<endl;
}

void library::load(){
    //读盘
    // 以读模式打开文件
    
    ifstream infile;
    string name;
    cout<<"请输入文件名：";
    cin>>name;
    
    infile.open(name,ios::in);
    char str[10*sizeof(string)];//用来读取文件中的一行（中介）
    stringstream ss;//用来将字符转换为int（中介的中介）
    
    //文件第一行特殊声明，表示该文件为 媒体库存储文件 ，方便以后的读取
    infile.getline(str, sizeof(str));
    while(strcmp(str,"<!DOCTYPE 媒体库存盘>")){
        cout<<"非存盘文件！请重新输入路径，或输入0返回：";
        cin>>name;
        if(name=="0")return;
        if(name=="")name="data.txt";
        infile.close();
        infile.open(name,ios::in);
        infile.getline(str, sizeof(str));
    }
    
    //监测到目标文件第一行为"<!DOCTYPE 媒体库存盘>"，则置零book、cd、drawing的数目
    book_count=0;
    cd_count=0;
    drawing_count=0;
    
    //声明，以准备数据读取
    string id,title,author;
    int grade;
    string publisher,ISBN;int page;
    string producer;int year,time;
    string nationality;int length,width;
    
    int bookcount,cdcount,drawingcount;
    
    //分别读入第2、3、4行book、cd、drawing的数目
    infile.getline(str, sizeof(str));
    ss<<str;ss>>bookcount;
    ss.clear();//清楚错误状态
    
    infile.getline(str, sizeof(str));
    ss<<str;ss>>cdcount;
    ss.clear();//清楚错误状态
    
    infile.getline(str, sizeof(str));
    ss<<str;ss>>drawingcount;
    ss.clear();//清楚错误状态
    
    //逐行读入book数据
    while (bookcount--) {
        infile.getline(str, sizeof(str));
        id=str;
        
        infile.getline(str, sizeof(str));
        title=str;
        
        infile.getline(str, sizeof(str));
        author=str;
        
        infile.getline(str, sizeof(str));
        ss<<str;ss>>grade;ss.clear();//清楚错误状态
        
        infile.getline(str, sizeof(str));
        publisher=str;
        
        infile.getline(str, sizeof(str));
        ISBN=str;
        
        infile.getline(str, sizeof(str));
        ss<<str;ss>>page;ss.clear();//清楚错误状态
        
        book b(id,title,author,(Grade)grade,publisher,ISBN,page);
        add_book(b);
    }
    
    //逐行读入cd数据
    while (cdcount--) {
        infile.getline(str, sizeof(str));
        id=str;
        
        infile.getline(str, sizeof(str));
        title=str;
        
        infile.getline(str, sizeof(str));
        author=str;
        
        infile.getline(str, sizeof(str));
        ss<<str;ss>>grade;ss.clear();//清楚错误状态
        
        infile.getline(str, sizeof(str));
        producer=str;
        
        infile.getline(str, sizeof(str));
        ss<<str;ss>>year;ss.clear();//清楚错误状态
        
        infile.getline(str, sizeof(str));
        ss<<str;ss>>time;ss.clear();//清楚错误状态
        
        cd c(id,title,author,(Grade)grade,producer,year,time);
        add_cd(c);
    }
    
    //逐行读入drawing数据
    while (drawingcount--) {
        infile.getline(str, sizeof(str));
        id=str;
        
        infile.getline(str, sizeof(str));
        title=str;
        
        infile.getline(str, sizeof(str));
        author=str;
        
        infile.getline(str, sizeof(str));
        ss<<str;ss>>grade;ss.clear();//清楚错误状态
        
        infile.getline(str, sizeof(str));
        nationality=str;
        
        infile.getline(str, sizeof(str));
        ss<<str;ss>>length;ss.clear();//清楚错误状态
        
        infile.getline(str, sizeof(str));
        ss<<str;ss>>width;ss.clear();//清楚错误状态
        
        drawing d(id,title,author,(Grade)grade,nationality,length,width);
        add_drawing(d);
    }
    infile.close();
    cout<<"成功从 "<<name<<" 读取数据！"<<endl;
    
}

//D.功能函数

//默认主菜单
void menu(){
    cout<<"*********************菜单栏**********************"<<endl;
    cout<<"请选择："<<endl;
    cout<<"1.添加物品"<<endl;
    cout<<"2.查询物品"<<endl;
    cout<<"3.显示物品库"<<endl;
    cout<<"4.编辑物品"<<endl;
    cout<<"5.删除物品"<<endl;
    cout<<"6.统计信息"<<endl;
    cout<<"7.物品存盘"<<endl;
    cout<<"8.读取信息"<<endl;
    cout<<"9.退出系统"<<endl<<endl;
}

//前置声明（add等函数要用到）
int choice(int number,library &l);

//对应“1.添加物品”选项
void add(library &l){
    cout<<"请选择："<<endl;
    cout<<"1.添加图书"<<endl;
    cout<<"2.添加视频光盘"<<endl;
    cout<<"3.添加图画"<<endl;
    cout<<"4.返回"<<endl<<endl;
    int number;
    cin>>number;
    cin.clear();//清除cin的错误状态
    cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
    if(number==4){
        menu();
        cin>>number;
        cin.clear();//清除cin的错误状态
        cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
        choice(number,l);
        return;
    }
    if(number!=1&&number!=2&&number!=3){
        cout<<"错误！请重新选择。"<<endl;
        add(l);
        return;
    }
    
    //预先声明变量，避免代码重用
    //基本
    string id;//编号
    string title;//标题
    string author;//作者
    Grade grade;//评级（未评级、一般、成人、儿童）
    
    //book
    string publisher;//出版社
    string ISBN;//ISBN号
    int page;//页数
    
    //cd
    string producer;//出品者的名字
    int year;//出品年份
    int time;//视频时长(秒)
    
    //drawing
    string nationality;//出品国籍
    int length;//作品的长（以厘米记，整数）
    int width;//作品的宽（以厘米记，整数）
    
    //基本
    cout<<"请输入编号：";
    cin>>id;
    cin.clear();//清除cin的错误状态
    cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
    //如果编号(id)重复，则重新输入
    while(l.whether_id_repeat(id)){
        cout<<"数据添加重复。"<<endl;
        cout<<"请输入编号：";
        cin>>id;
        cin.clear();//清除cin的错误状态
        cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
    }
    cout<<"请输入标题：";
    cin>>title;
    cout<<"请输入作者：";
    cin>>author;
    cout<<"请输入评级(输入0、1、2、3分别表示未评级、一般、成人、儿童)：";
    int a;
    cin>>a;
    cin.clear();//清除cin的错误状态4
    cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
    while(a!=0&&a!=1&&a!=2&&a!=3){
        cout<<"请重新输入正确的序号！"<<endl;
        cin>>a;
        cin.clear();//清除cin的错误状态
        cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
    }
    grade=(Grade)a;
    switch (number) {
        case 1:
        {
            cout<<"请输入出版社：";
            cin>>publisher;
            cout<<"请输入ISBN号：";
            cin>>ISBN;
            cout<<"请输入页数：";
            cin>>page;
            cin.clear();//清除cin的错误状态
            cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
            book b(id,title,author,grade,publisher,ISBN,page);
            l.add_book(b);
            cout<<endl;
        }
            break;
        
        case 2:
        {
            cout<<"请输入出品者的名字：";
            cin>>producer;
            cout<<"请输入出品年份：";
            cin>>year;
            cin.clear();//清除cin的错误状态
            cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
            cout<<"请输入视频时长(秒)：";
            cin>>time;
            cin.clear();//清除cin的错误状态
            cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
            cd c(id,title,author,grade,producer,year,time);
            l.add_cd(c);
            cout<<endl;
        }
            break;
        case 3:
        {
            cout<<"请输入出品国籍：";
            cin>>nationality;
            cout<<"请输入作品的长（以厘米记，整数）：";
            cin>>length;
            cin.clear();//清除cin的错误状态
            cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
            cout<<"请输入作品的宽（以厘米记，整数）：";
            cin>>width;
            cin.clear();//清除cin的错误状态
            cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
            drawing d(id,title,author,grade,nationality,length,width);
            l.add_drawing(d);
            cout<<endl;
        }
            break;
            //事实上无需defalut，因为前面代码已经确保了number必为1、2、3其中之一。
        default:
            cout<<"未知错误！"<<endl;
            //add(l);
            break;
            
    }
}

//对应“2.查询物品“选项
void query(library l){
    cout<<"请选择："<<endl;
    cout<<"1.按标题查询"<<endl;
    cout<<"2.按编号查询"<<endl;
    cout<<"3.按类别查询"<<endl;
    cout<<"4.返回"<<endl<<endl;
    int number;
    cin>>number;
    cin.clear();//清除cin的错误状态
    cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
    if(number==4){
        menu();
        cin>>number;
        cin.clear();//清除cin的错误状态
        cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
        choice(number,l);
        return;
    }
    if(number!=1&&number!=2&&number!=3){
        cout<<"错误！请重新选择。"<<endl;
        add(l);
        return;
    }
    switch (number) {
        case 1:
        {
            cout<<"请输入标题：";
            string title;
            cin>>title;
            int exist=l.does_title_exist(title);
            //如果不存在，则提示
            if(!exist)cout<<"该标题不存在！"<<endl;
        }
            break;
        case 2:
        {
            cout<<"请输入编号：";
            string id;
            cin>>id;
            int exist=l.does_id_exist(id);
            //如果不存在，则提示
            if(!exist)cout<<"该编号不存在！"<<endl;
        }
            break;
        case 3:
        {
            cout<<"请输入类别（1.图书，2.视频光盘，3.图画）（输入序号）：";
            int category=0;
            cin>>category;
            cin.clear();//清除cin的错误状态
            cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
            while(category!=1&&category!=2&&category!=3){
                cout<<"请输入正确的序号！"<<endl;
                cout<<"请输入类别（1.图书，2.视频光盘，3.图画）（输入序号）：";
                cin>>category;
                cin.clear();//清除cin的错误状态
                cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
            }
            int exist=l.check_category(category);
            //如果不存在，则提示
            if(!exist)cout<<"该类别没有物品！"<<endl;
        }
            break;
            //事实上无需defalut，因为前面代码已经确保了number必为1、2、3其中之一。
        default:
            cout<<"未知错误！"<<endl;
            //add(l);
            break;
    }
}

//library类的show()对应”3.显示物品库“选项

//对应”4.编辑物品“选项
void edit(library &l){
    string id;
    cout<<"请输入想要修改的编号：";
    cin>>id;
    int exist=l.does_id_exist(id);
    //如果不存在，则提示
    if(!exist){
        cout<<"该编号不存在！"<<endl<<endl;
        return;
    }
    else{
        cout<<"您想修改以下哪项？"<<endl;
        cout<<"1.编号 2.标题 3.作者 4.评级 ";
        //若为book
        if(exist==1){
            cout<<"5.出版社 6.ISBN号 7.页数";
            int select;
            cin>>select;
            cin.clear();//清除cin的错误状态
            cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
            if(select==1){
                cout<<"请输入新的编号：";
                for(int i=0;i<l.get_book_count();i++){
                    if(id==l.get_books()[i].getId()){
                        string p;
                        int subexist;
                        //判断输入的新编号重不重号
                        do{
                            cin>>p;
                            subexist=l.does_id_exist(p);
                            if(subexist){
                                cout<<"编号重复！请重新输入：";
                            }
                        }
                        while(subexist);
                        l.get_books()[i].set_id(p);
                    }
                }
            }
            if(select==2){
                cout<<"请输入新的标题：";
                for(int i=0;i<l.get_book_count();i++){
                    if(id==l.get_books()[i].getId()){
                        string p;
                        cin>>p;
                        l.get_books()[i].set_title(p);
                    }
                }
            }
            if(select==3){
                cout<<"请输入新的作者：";
                for(int i=0;i<l.get_book_count();i++){
                    if(id==l.get_books()[i].getId()){
                        string p;
                        cin>>p;
                        l.get_books()[i].set_author(p);
                    }
                }
            }
            if(select==4){
                cout<<"请输入新的评级(输入0、1、2、3分别表示未评级、一般、成人、儿童)：";
                for(int i=0;i<l.get_book_count();i++){
                    if(id==l.get_books()[i].getId()){
                        int p;
                        cin>>p;
                        cin.clear();//清除cin的错误状态
                        cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
                        while(p!=0&&p!=1&&p!=2&&p!=3){
                            cout<<"请重新输入正确的序号！"<<endl;
                            cin>>p;
                            cin.clear();//清除cin的错误状态
                            cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
                        }
                        l.get_books()[i].set_grade((Grade)p);
                    }
                }
            }
            if(select==5){
                cout<<"请输入新的出版社：";
                for(int i=0;i<l.get_book_count();i++){
                    if(id==l.get_books()[i].getId()){
                        string p;
                        cin>>p;
                        l.get_books()[i].set_publisher(p);
                    }
                }
            }
            if(select==6){
                cout<<"请输入新的ISBN号：";
                for(int i=0;i<l.get_book_count();i++){
                    if(id==l.get_books()[i].getId()){
                        string p;
                        cin>>p;
                        l.get_books()[i].set_ISBN(p);
                    }
                }
            }
            if(select==7){
                cout<<"请输入新的页数：";
                for(int i=0;i<l.get_book_count();i++){
                    if(id==l.get_books()[i].getId()){
                        int p;
                        cin>>p;
                        cin.clear();//清除cin的错误状态
                        cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
                        l.get_books()[i].set_Page(p);
                    }
                }
            }
        }
        //若为cd
        if(exist==2){
            cout<<"5.出品者 6.出品年份 7.视频时长";
            int select;
            cin>>select;
            cin.clear();//清除cin的错误状态
            cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
            if(select==1){
                cout<<"请输入新的编号：";
                for(int i=0;i<l.get_cd_count();i++){
                    if(id==l.get_cds()[i].getId()){
                        string p;
                        int subexist;
                        //判断输入的新编号重不重号
                        do{
                            cin>>p;
                            subexist=l.does_id_exist(p);
                            if(subexist){
                                cout<<"编号重复！请重新输入：";
                            }
                        }while(subexist);
                        l.get_cds()[i].set_id(p);
                    }
                }
            }
            if(select==2){
                cout<<"请输入新的标题：";
                for(int i=0;i<l.get_cd_count();i++){
                    if(id==l.get_cds()[i].getId()){
                        string p;
                        cin>>p;
                        l.get_cds()[i].set_title(p);
                    }
                }
            }
            if(select==3){
                cout<<"请输入新的作者：";
                for(int i=0;i<l.get_cd_count();i++){
                    if(id==l.get_cds()[i].getId()){
                        string p;
                        cin>>p;
                        l.get_cds()[i].set_author(p);
                    }
                }
            }
            if(select==4){
                cout<<"请输入新的评级(输入0、1、2、3分别表示未评级、一般、成人、儿童)：";
                for(int i=0;i<l.get_cd_count();i++){
                    if(id==l.get_cds()[i].getId()){
                        int p;
                        cin>>p;
                        cin.clear();//清除cin的错误状态
                        cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
                        while(p!=0&&p!=1&&p!=2&&p!=3){
                            cout<<"请重新输入正确的序号！"<<endl;
                            cin>>p;
                            cin.clear();//清除cin的错误状态
                            cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
                        }
                        l.get_cds()[i].set_grade((Grade)p);
                    }
                }
            }
            if(select==5){
                cout<<"请输入新的出品者名字：";
                for(int i=0;i<l.get_cd_count();i++){
                    if(id==l.get_cds()[i].getId()){
                        string p;
                        cin>>p;
                        l.get_cds()[i].set_producer(p);
                    }
                }
            }
            if(select==6){
                cout<<"请输入新的出品年份：";
                for(int i=0;i<l.get_cd_count();i++){
                    if(id==l.get_cds()[i].getId()){
                        int p;
                        cin>>p;
                        cin.clear();//清除cin的错误状态
                        cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
                        l.get_cds()[i].set_year(p);
                    }
                }
            }
            if(select==7){
                cout<<"请输入新的视频时长（秒）：";
                for(int i=0;i<l.get_cd_count();i++){
                    if(id==l.get_cds()[i].getId()){
                        int p;
                        cin>>p;
                        cin.clear();//清除cin的错误状态
                        cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
                        l.get_cds()[i].set_time(p);
                    }
                }
            }
        }
        //若为drawing
        if(exist==3){
            cout<<"5.出品国籍 6.作品的长 7.作品的宽";
            int select;
            cin>>select;
            cin.clear();//清除cin的错误状态
            cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
            if(select==1){
                cout<<"请输入新的编号：";
                for(int i=0;i<l.get_drawing_count();i++){
                    if(id==l.get_drawings()[i].getId()){
                        string p;
                        int subexist;
                        //判断输入的新编号重不重号
                        do{
                            cin>>p;
                            subexist=l.does_id_exist(p);
                            if(subexist){
                                cout<<"编号重复！请重新输入：";
                            }
                        }while(subexist);
                        l.get_drawings()[i].set_id(p);
                    }
                }
            }
            if(select==2){
                cout<<"请输入新的标题：";
                for(int i=0;i<l.get_drawing_count();i++){
                    if(id==l.get_drawings()[i].getId()){
                        string p;
                        cin>>p;
                        l.get_drawings()[i].set_title(p);
                    }
                }
            }
            if(select==3){
                cout<<"请输入新的作者：";
                for(int i=0;i<l.get_drawing_count();i++){
                    if(id==l.get_drawings()[i].getId()){
                        string p;
                        cin>>p;
                        l.get_drawings()[i].set_author(p);
                    }
                }
            }
            if(select==4){
                cout<<"请输入新的评级(输入0、1、2、3分别表示未评级、一般、成人、儿童)：";
                for(int i=0;i<l.get_drawing_count();i++){
                    if(id==l.get_drawings()[i].getId()){
                        int p;
                        cin>>p;
                        cin.clear();//清除cin的错误状态
                        cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
                        while(p!=0&&p!=1&&p!=2&&p!=3){
                            cout<<"请重新输入正确的序号！"<<endl;
                            cin>>p;
                            cin.clear();//清除cin的错误状态
                            cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
                        }
                        l.get_drawings()[i].set_grade((Grade)p);
                    }
                }
            }
            if(select==5){
                cout<<"请输入新的出品国籍：";
                for(int i=0;i<l.get_drawing_count();i++){
                    if(id==l.get_drawings()[i].getId()){
                        string p;
                        cin>>p;
                        l.get_drawings()[i].set_nationality(p);
                    }
                }
            }
            if(select==6){
                cout<<"请输入新的作品长（以厘米记，整数）：";
                for(int i=0;i<l.get_drawing_count();i++){
                    if(id==l.get_drawings()[i].getId()){
                        int p;
                        cin>>p;
                        cin.clear();//清除cin的错误状态
                        cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
                        l.get_drawings()[i].set_length(p);
                    }
                }
            }
            if(select==7){
                cout<<"请输入新的作品宽（以厘米记，整数）：";
                for(int i=0;i<l.get_drawing_count();i++){
                    if(id==l.get_drawings()[i].getId()){
                        int p;
                        cin>>p;
                        cin.clear();//清除cin的错误状态
                        cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
                        l.get_drawings()[i].set_width(p);
                    }
                }
            }
        }
        cout<<endl;
    }
}

//对应”5.删除物品“选项
void del(library &l){
    if(l.get_book_count()+l.get_cd_count()+l.get_drawing_count()==0){
        cout<<"物品库为空！"<<endl;
        return;
    }
    string id;
    cout<<"输入要删除的编号：";
    cin>>id;
    int exist=l.does_id_exist(id);
    if (!exist) {
        cout<<"该编号不存在！"<<endl<<endl;
        return;
    }else{
        string verify="";
        cout<<"确定要删除编号为"<<id<<"的物品吗？"<<endl;
        cout<<"输入123以删除:";
        cin>>verify;
        cout<<endl;
        cin.clear();//清除cin的错误状态
        cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
        if(verify=="123")l.remove(exist, id);
        else cout<<"已取消删除。"<<endl;
    }
    cout<<endl;
    
}


//library类的statistics()对应”6.统计信息“选项
//library类的save()对应”7.物品存盘“选项
//library类的load()对应”8.读取信息“选项


//number是输入的数字，l是物品仓库类
//该函数负责：根据输入的数字调用函数
int choice(int number,library &l){
    switch (number) {
        case 1:
            add(l);
            break;
        case 2:
            query(l);
            break;
        case 3:
            l.show();
            break;
        case 4:
            edit(l);
            break;
        case 5:
            del(l);
            break;
        case 6:
            l.statistics();
            break;
        case 7:
            l.save();
            break;
        case 8:
            l.load();
            break;
        case 9:
            exit(0);
            break;
            
        default:
            cout<<"错误！请重新选择:"<<endl;
            cin>>number;
            cin.clear();//清除cin的错误状态
            cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
            number=choice(number,l);
            break;
    }
    return number;
}


//E.main函数

int main() {
    library l;
    int situation;
    int number;
    menu();
    while(1){
        cin>>number;
        cin.clear();//清除cin的错误状态
        cin.ignore();//忽略掉缓冲区的内容，直到遇到EOF为止
        situation=choice(number,l);
        if(situation-6<0)menu();cout<<endl;
    }
    return 0;
}
