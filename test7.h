#include "iostream"
#include "limits"
#include "sstream"
#include "fstream"
using namespace std;
struct goods
{
    int type;
    int num;
    float price;
};
const char* file="goods.dat";
class Data
{
public:
    Data(int number,float Price):num(number),price(Price){}
    virtual ~Data(){};
    int GetNumber()const{return num;}
    float GetPrice()const{return price;}
    virtual void Print()const=0;
private:
    int num;
    float price;
};
class Book:public Data
{
public:
    Book(int number,float Price);
    virtual void Print()const
    {
        cout<<"图书编号为："<<GetNumber()<<endl;
        cout<<"图书价格为："<<GetPrice()<<endl;
    }
};
Book::Book(int number,float Price):Data(number,Price){}//初始化基类部分
class Drug:public Data
{
public:
    Drug(int number,float Price);
    virtual void Print()const
    {
        cout<<"药品编号为："<<GetNumber()<<endl;
        cout<<"药品价格为："<<GetPrice()<<endl;
    }
};
Drug::Drug(int number,float Price):Data(number,Price){}
class Node
{
public:
    Node(Data*);
    ~Node();
    void SetNext(Node* node){itsNext=node;}
    Node* GetNext()const;
    Data* GetData()const;

private:
    Data* itsData;
    Node* itsNext;
};
Node::Node(Data*pData):itsData(pData),itsNext(0){}
Node::~Node(){delete itsData;itsData=0;}
Node* Node::GetNext()const
{
    return itsNext;

}
Data* Node::GetData()const
{
    if(itsData)
        return itsData;
    else
        return NULL;
}

class List
{
public:
    List();
    ~List();
    Data* Find(int number)const;
    Data* Find(int &increase,int number)const;
    int GetCount()const{return count;}
    Data* GetFirst()const;
    void Insert(Data*);
    void Show()const;
    Data* operator[](int)const;
    void Delete(int num);
private:
    Node* head;
    int count;
};
List::List():head(0),count(0){}
List::~List()
{
    Node* l=head;
    Node* m=0;
    int n=0;
    while(1)
    {
        m=l;
        l=l->GetNext();
        n++;
        cout<<"程序结束，删除第"<<n<<"个节点";
        delete m;

    }
}
Data* List::GetFirst()const
{
    if(head)
        return head->GetData();
    else
        return NULL;

}
Data* List::operator[](int offset)const
{
    Node* pn=head;
    if(!head)
        return NULL;
    if(offset>=count)
        return NULL;
    for(int i=0;i<offset;i++)
        pn=pn->GetNext();
    return pn->GetData();
}

Data* List::Find(int number)const
{
    Node* pn=0;
    for(pn=head;pn!=NULL;pn=pn->GetNext())
    {
        if(pn->GetData()->GetNumber()==number)
            break;

    }
    if(pn==NULL)
        return NULL;
    else
        return pn->GetData();
}
Data* List::Find(int &increase,int number)const
{
    Node*pn=0;
    for(pn=head,increase=0;pn!=NULL;pn=pn->GetNext(),increase++)
    {
        if(pn->GetData()->GetNumber()==number)
            break;

    }
    if(pn==NULL)
        return NULL;
    else
        return pn->GetData();
}
void List::Show()const
{
    if(!head)
        return ;
    Node* pn=head;
    do
        pn->GetData()->Print();
    while(pn=pn->GetNext());

}
void List::Delete(int num)
{
    Node*pBack=head;
    Node*pNow=head;
    if(!head)
    {
        cout<<"没有数据可以删除"<<endl;
        return ;
    }

    if (head->GetData()->GetNumber()==num)
    {
        if(!head->GetNext())
        {
        delete head;
        cout<<"数据被清空"<<endl;
        head=0;
        count--;
        return ;
    }
    else
    {
        head=head->GetNext();
        delete pNow;
        pNow=0;
        cout<<"删除成功"<<endl;
        count--;
        return ;
    }
}
while(pBack)
{
    if(pBack->GetNext()==NULL)
    {
        cout<<"找不到要删除的编号"<<endl;
        return ;
    }
    if(pBack->GetNext()->GetData()->GetNumber()==num)
    {
        pNow=pBack->GetNext();
        pBack->SetNext(pNow->GetNext());
        cout<<"删除数据成功"<<endl;
        count--;
        return ;
    }
    pBack=pBack->GetNext();
}
cout<<"不存在此编号"<<endl;
}
void List::Insert(Data*pData)
{
    Node*pn=new Node(pData);
    Node *pNow=head;
    Node *pNext=0;
    int New=pData->GetNumber();
    int next=0;
    count++;
    if(!head)
    {
        head=pn;
        return ;
    }
    if(head->GetData()->GetNumber()>New)
    {
        pn->SetNext(head);
        head=pn;
        return ;
    }
    for(;;)
    {
        if(!pNow->GetNext())
        {
            pNow->SetNext(pn);
            return;

        }
        pNext=pNow->GetNext();
        next=pNext->GetData()->GetNumber();
        if(next>New)
        {
            pNow->SetNext(pn);
            pn->SetNext(pNext);
            return ;
        }
        pNow=pNext;
    }
}
class Repair:private List
{
public:
    void RInsert(Data*);
    void Run();
private:

};
void Repair::RInsert(Data*newdata)
{
    int num=newdata->GetNumber();
    int place=0;
    if(!Find(place,num))
        Insert(newdata);
    else
    {
        cout<<"已经存在"<<endl;
    }
}
void Repair::Run()
{
   // List pl;
    Data* pData=0;
    int number;
    float price;
    int choice;
    bool quit=false;
    while(1)
    {
        system("cls");
        cout<<"(1)增加商品(2)列出所有的商品(3)删除商品(4)查找商品(5)商品数目(6)退出(7)读取文件（8）写入到文件";
        cin>>choice;
        switch(choice)
        {
        case 1:
            while(1)
            {
                cout<<"(0)turn back(1)books(2)madicine:";
                cin>>choice;
                if(!choice)
                {
                    break;
                }
                else if(choice==1||choice==2)
                {
                    cout<<"please input the number";
                    cin>>number;
                    if(choice==1)
                    {
                        cout<<"please input the price of the book";
                        cin>>price;
                        pData=new Book(number,price);
                        RInsert(pData);


                    }
                    else if(choice==2)
                    {
                        cout<<"please input the price of the madicine";
                        cin>>price;
                        pData=new Drug(number,price);
                       RInsert(pData);
                    }
                }
                else
                    cout<<"please input the number from 0 to 2";

            }
            break;
        case 2:
            if(GetFirst()==0)
            {
                cout<<"你的商品为空，请增加商品，\n"<<"按回车键返回主窗口"<<endl;
                cin.get();
                cin.get();

            }
            else
            {
                Show();
                cout<<"请按回车键返回主窗口"<<endl;
                cin.get();
                cin.get();

            }
            break;
        case 3:
            cout<<"请输入你要删除的商品编号："<<endl;
            cin>>number;
    Delete(number);
            cin.get();
            cin.get();
            break;
        case 4:
            while(1)
            {
                cout<<"(0)返回(1)按编号查询(2)按序号查询："<<endl;
                cin>>choice;
                if(!choice)
                {
                    break;
                }
                if(choice==1)
                {
                    cout<<"请输入所要查询的商品编号："<<endl;
                    cin>>number;
                    Data* result=Find(number);
                    if(result==0)
                        cout<<"can not find"<<endl;
                    else
                        result->Print();

                }
                else if(choice==2)
                {
                    cout<<"请输入所要查找的数据的序号："<<endl;
                    cin>>number;
                    if((*this)[number-1])
                    {
                        (*this)[number-1]->Print();
                    }
                    else
                         cout<<"找不到你所要查询的数据"<<endl;

                }
                else
                    cout<<"请输入0-2之间的数字\n"<<endl;
            }
            break;
        case 5:
            cout<<"该链表共有"<<GetCount()<<"节点"<<endl;
            cin.get();
            cin.get();
            break;
        case 6:
            quit=true;
            break;
        case 7:
            {
            fstream In;
            int num=0;
            In.open(file,ios::in|ios::out|ios::binary);
            if(In.is_open())
            {
                In.seekp(0);
                string ch;
                In>>ch;
                stringstream ssout;
                ssout<<ch;
                ssout>>num;
                cout<<"当前内容为"<<file<<"\n";
                if(num==0)
                {
                    cout<<"文件读取成功。\n";
                    cout<<"当前文件为空"<<endl;
                    cin.get();
                    break;

                }
                cout<<"读入"<<num<<"个商品记录"<<endl;
                In.ignore();
                goods pp={0};
                while(In.read((char*)&pp,sizeof pp))
                {
                    if(pp.type==1)
                    {
                        pData=new Book(pp.num,pp.price);
                        RInsert(pData);
                    }
                    else if(pp.type==2)
                    {
                        pData=new Drug(pp.num,pp.price);
                        RInsert(pData);
                    }
                    else
                        continue;

                }
                if(In.eof())
                    In.clear();
                else
                   {

                    cerr<<"文件读取错误"<<endl;
                    exit(1);
                   }

            }
            else
            {
                cerr<<file<<"不能打开"<<endl;
                exit(1);

            }
            Show();
            cout<<"读取成功"<<endl;
            cin.get();
            cin.get();
            In.close();
            }
            break;
        case 8:
            {
                int num=GetCount();
                goods *pp=new goods[num];
                ofstream fout(file,ios::out|ios::binary);
                fout<<num<<" ";
                for(int i=0;i<num;i++)
                {
                    Data *p=(*this)[i];
                    if(p)
                    {
                        if(typeid(*p).name()==typeid(Book).name())
                        {
                            pp->type=1;
                            cout<<"存入商品类型：图书"<<"\t";
                        }
                        else if(typeid(*p).name()==typeid(Drug).name())
                        {
                            pp->type=2;
                            cout<<"存入商品类型：药品"<<"\t";
                        }
                        else
                        {
                            pp->type=0;
                            cout<<"无商品类型。"<<endl;

                        }
                        pp->num=p->GetNumber();
                        cout<<"编号："<<pp->num<<"\t";
                        pp->price=p->GetPrice();
                        cout<<"价格："<<pp->price<<endl;
                        cin.get();
                        fout.write((char*)&(*pp),sizeof (*pp) );

                    }
                    else
                        break;
                    p++;
                }
                cout<<"保存成功"<<endl;
                cin.get();
                fout.close();
            }
            break;
        default:
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"你只可以输入1-6之间的数，请重新输入"<<endl<<"按回车键返回并重新录入"<<endl;
            cin.get();
            break;





       }
        if(quit)
        {


        cout<<"程序结束"<<endl;
        cin.get();
        break;
        }
    }
    exit(0);

}

