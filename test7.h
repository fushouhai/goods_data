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
        cout<<"ͼ����Ϊ��"<<GetNumber()<<endl;
        cout<<"ͼ��۸�Ϊ��"<<GetPrice()<<endl;
    }
};
Book::Book(int number,float Price):Data(number,Price){}//��ʼ�����ಿ��
class Drug:public Data
{
public:
    Drug(int number,float Price);
    virtual void Print()const
    {
        cout<<"ҩƷ���Ϊ��"<<GetNumber()<<endl;
        cout<<"ҩƷ�۸�Ϊ��"<<GetPrice()<<endl;
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
        cout<<"���������ɾ����"<<n<<"���ڵ�";
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
        cout<<"û�����ݿ���ɾ��"<<endl;
        return ;
    }

    if (head->GetData()->GetNumber()==num)
    {
        if(!head->GetNext())
        {
        delete head;
        cout<<"���ݱ����"<<endl;
        head=0;
        count--;
        return ;
    }
    else
    {
        head=head->GetNext();
        delete pNow;
        pNow=0;
        cout<<"ɾ���ɹ�"<<endl;
        count--;
        return ;
    }
}
while(pBack)
{
    if(pBack->GetNext()==NULL)
    {
        cout<<"�Ҳ���Ҫɾ���ı��"<<endl;
        return ;
    }
    if(pBack->GetNext()->GetData()->GetNumber()==num)
    {
        pNow=pBack->GetNext();
        pBack->SetNext(pNow->GetNext());
        cout<<"ɾ�����ݳɹ�"<<endl;
        count--;
        return ;
    }
    pBack=pBack->GetNext();
}
cout<<"�����ڴ˱��"<<endl;
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
        cout<<"�Ѿ�����"<<endl;
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
        cout<<"(1)������Ʒ(2)�г����е���Ʒ(3)ɾ����Ʒ(4)������Ʒ(5)��Ʒ��Ŀ(6)�˳�(7)��ȡ�ļ���8��д�뵽�ļ�";
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
                cout<<"�����ƷΪ�գ���������Ʒ��\n"<<"���س�������������"<<endl;
                cin.get();
                cin.get();

            }
            else
            {
                Show();
                cout<<"�밴�س�������������"<<endl;
                cin.get();
                cin.get();

            }
            break;
        case 3:
            cout<<"��������Ҫɾ������Ʒ��ţ�"<<endl;
            cin>>number;
    Delete(number);
            cin.get();
            cin.get();
            break;
        case 4:
            while(1)
            {
                cout<<"(0)����(1)����Ų�ѯ(2)����Ų�ѯ��"<<endl;
                cin>>choice;
                if(!choice)
                {
                    break;
                }
                if(choice==1)
                {
                    cout<<"��������Ҫ��ѯ����Ʒ��ţ�"<<endl;
                    cin>>number;
                    Data* result=Find(number);
                    if(result==0)
                        cout<<"can not find"<<endl;
                    else
                        result->Print();

                }
                else if(choice==2)
                {
                    cout<<"��������Ҫ���ҵ����ݵ���ţ�"<<endl;
                    cin>>number;
                    if((*this)[number-1])
                    {
                        (*this)[number-1]->Print();
                    }
                    else
                         cout<<"�Ҳ�������Ҫ��ѯ������"<<endl;

                }
                else
                    cout<<"������0-2֮�������\n"<<endl;
            }
            break;
        case 5:
            cout<<"��������"<<GetCount()<<"�ڵ�"<<endl;
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
                cout<<"��ǰ����Ϊ"<<file<<"\n";
                if(num==0)
                {
                    cout<<"�ļ���ȡ�ɹ���\n";
                    cout<<"��ǰ�ļ�Ϊ��"<<endl;
                    cin.get();
                    break;

                }
                cout<<"����"<<num<<"����Ʒ��¼"<<endl;
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

                    cerr<<"�ļ���ȡ����"<<endl;
                    exit(1);
                   }

            }
            else
            {
                cerr<<file<<"���ܴ�"<<endl;
                exit(1);

            }
            Show();
            cout<<"��ȡ�ɹ�"<<endl;
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
                            cout<<"������Ʒ���ͣ�ͼ��"<<"\t";
                        }
                        else if(typeid(*p).name()==typeid(Drug).name())
                        {
                            pp->type=2;
                            cout<<"������Ʒ���ͣ�ҩƷ"<<"\t";
                        }
                        else
                        {
                            pp->type=0;
                            cout<<"����Ʒ���͡�"<<endl;

                        }
                        pp->num=p->GetNumber();
                        cout<<"��ţ�"<<pp->num<<"\t";
                        pp->price=p->GetPrice();
                        cout<<"�۸�"<<pp->price<<endl;
                        cin.get();
                        fout.write((char*)&(*pp),sizeof (*pp) );

                    }
                    else
                        break;
                    p++;
                }
                cout<<"����ɹ�"<<endl;
                cin.get();
                fout.close();
            }
            break;
        default:
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"��ֻ��������1-6֮�����������������"<<endl<<"���س������ز�����¼��"<<endl;
            cin.get();
            break;





       }
        if(quit)
        {


        cout<<"�������"<<endl;
        cin.get();
        break;
        }
    }
    exit(0);

}

