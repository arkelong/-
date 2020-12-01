//ʹ�õݹ��½�������
//ͷ�ļ�
#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string in;//����
//�ʷ�����
string instr;//������Ŵ�
int index;//��ǰ������Ŷ����ַ���λ��
char character;//ȫ�ֱ����ַ���������¶�����ַ�
string token;//�ַ����飬����Ѷ�����ַ�����

map<string, int> Symbol;//δ�����ʶ����<��ʶ��,map�������±�>
map<string, int> DefSymbol;//�Ѷ����ʶ����
map<string, int> Digit;//������
map<string, int>::iterator it;
const int len = 50;
string Reserve[len];//�����ֱ�
string Operator[2 * len];//�����
string Boundary[3 * len];//���
struct Binary {
	Binary(int c, int i, string v = "-") {
		category = c;
		index = i;
		value = v;
	}
	Binary() {}
	int category = 0;//���
	int index = 0;//��Ӧ��ʶ���ڱ�ʶ����λ�û���ֵ�ڳ������λ��
	string value = "-";//��ʶ������ֵ
};

struct Binary all[100];//���е���
int ip;//���е��ʼ��±�

void init_Reserve() {//���챣���ֱ�ĺ���
	Reserve[1] = "main";
	Reserve[2] = "var";
	Reserve[3] = "integer";
	Reserve[4] = "real";
	Reserve[5] = "";
	Reserve[6] = "";
	Reserve[7] = "while";
	Reserve[8] = "do";
	Reserve[9] = "if";
	Reserve[10] = "then";
	Reserve[11] = "else";
	Reserve[12] = "or";
	Reserve[13] = "and";
	Reserve[14] = "not";
}
void init_Operator() {//��ʼ���������
	Operator[50] = ":=";
	Operator[51] = "+";
	Operator[52] = "-";
	Operator[53] = "*";
	Operator[54] = "/";
	Operator[55] = "<";
	Operator[56] = "<=";
	Operator[57] = ">";
	Operator[58] = ">=";
	Operator[59] = "==";
	Operator[60] = "!=";
}
void init_Boundary() {//������ʼ��
	Boundary[100] = "(";
	Boundary[101] = ")";
	Boundary[102] = ",";
	Boundary[103] = ":";
	Boundary[104] = ";";
	Boundary[105] = "{";
	Boundary[106] = "}";
	Boundary[107] = "#";
}

void getChar() {//����һ���ַ�
	character = instr[index++];
}
void getnbc() {//����ǿհ��ַ�
	while (character == ' ') {
		getChar();
	}
}
void concat() {//�����ַ���
	token = token + character;
}
bool letter() {//�ж��Ƿ�Ϊ��ĸ
	if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z'))
		return true;
	return false;
}
bool digit() {//�ж��Ƿ�Ϊ����
	if (character >= '0' && character <= '9')
		return true;
	return false;
}
void retract() {//�����ַ��ĺ���
	character = ' ';
	index--;
}
int reserve() {//ƥ�䱣���ַ�
	for (int i = 0; i < len; i++)
		if (Reserve[i] == token)return i;
	return -1;
}
string symbol() {
	it = Symbol.find(token);//���ұ����Ƿ��Ѵ��ڸñ�ʶ��
	if (it != Symbol.end()) {//����
		return it->first;//���ظñ�ʶ��
	}
	else {//������
		Symbol[token] = Symbol.size();
		return token;
	}
}
bool defSymbol(string defSym,bool push) { //defSym��ʾ����push�����Ƿ�����Ѷ����ʶ������
	it = DefSymbol.find(defSym);//���ұ����Ƿ��Ѵ��ڸñ�ʶ��
	if (it != DefSymbol.end()) {//����
		return true;//����true
	}
	else {//������
		if (push) {//�����Ѷ����ʶ������
			DefSymbol[defSym] = DefSymbol.size();
		}
		return false;//����false
	}
}
string constant() {
	it = Digit.find(token);
	if (it != Digit.end()) {
		return it->first;
	}
	else {
		Digit[token] = Digit.size();
		return token;
	}
}
Binary error() {
	cout << token << "\t-->\t�õ��ʲ�����" << endl;
	return Binary(0, 0);
}
//�ʷ��������������ʶ�𵥴�
Binary LexAnalyze() {
	token = "";
	getChar();
	getnbc();
	string val;
	int num = -1;
	switch (character) {
	case'a':
	case'b':
	case'c':
	case'd':
	case'e':
	case'f':
	case'g':
	case'h':
	case'i':
	case'j':
	case'k':
	case'l':
	case'm':
	case'n':
	case'o':
	case'p':
	case'q':
	case'r':
	case's':
	case't':
	case'u':
	case'v':
	case'w':
	case'x':
	case'y':
	case'z':
	case'A':
	case'B':
	case'C':
	case'D':
	case'E':
	case'F':
	case'G':
	case'H':
	case'I':
	case'J':
	case'K':
	case'L':
	case'M':
	case'N':
	case'O':
	case'P':
	case'Q':
	case'R':
	case'S':
	case'T':
	case'U':
	case'V':
	case'W':
	case'X':
	case'Y':
	case'Z':
		while (letter() || digit()) {//Ϊ��ĸ������
			concat();//׷�ӵ�tokenĩβ
			getChar();//��ȡ��һ���ַ�
		}
		retract();//����һ���ַ�
		num = reserve();//�鿴�����ֱ�
		if (num != -1) {
			return Binary(num, 0,Reserve[num]);
		}
		else {
			val = symbol();//�鿴��ʶ����
			return Binary(39, Symbol[val], val);//index��1��ʼ
		}
		break;
	case'0':
	case'1':
	case'2':
	case'3':
	case'4':
	case'5':
	case'6':
	case'7':
	case'8':
	case'9':
		while (digit()) {//Ϊ����
			concat();
			getChar();
		}
		retract();
		val = constant();//�鿴������
		return Binary(40, Digit[val], val);
		break;
	case'<':
		getChar();
		if (character == '=') return Binary(56, 0, Operator[56]);//����<=����
		else {
			retract();
			return Binary(55, 0, Operator[55]);//����<����
		}
		break;
	case'>':
		getChar();
		if (character == '=')return Binary(58, 0, Operator[58]);//����>=����
		else {
			retract();
			return Binary(57, 0, Operator[57]);//����>����
		}
		break;
	case'=':
		getChar();
		if (character == '=') return Binary(59, 0, Operator[59]);//����==����
		else {
			retract();
			return error();// ����
		}
		break;
	case'!':
		getChar();
		if (character == '=')return Binary(60, 0, Boundary[60]);
		else return error();
		break;
	case'+':
		return Binary(51, 0, Operator[51]);
		break;
	case'-':
		return Binary(52, 0, Operator[52]);
		break;
	case'*':
		return Binary(53, 0, Operator[53]);
		break;
	case'/':
		return Binary(54, 0, Operator[54]);
		break;
	case'(':
		return Binary(100, 0, Boundary[100]);
		break;
	case')':
		return Binary(101, 0, Boundary[101]);
		break;
	case',':
		return Binary(102, 0, Boundary[102]);
		break;
	case':':
		getChar();
		if (character == '=')return Binary(50, 0, Operator[50]);
		else {
			retract();
			return Binary(103, 0, Boundary[103]);
		}
		break;
	case';':
		return Binary(104, 0, Boundary[104]);
		break;
	case'{':
		return Binary(105, 0, Boundary[105]);
		break;
	case'}':
		return Binary(106, 0, Boundary[106]);
		break;
	case'#':
		return Binary(107, 0, Boundary[107]);
		break;
	default:
		return error();
	}
}

void show_table() {
	cout << "\n==================" << "��ʶ��" << "==================" << endl;
	cout << "��ʶ��\t\t������\t����λ��" << endl;
	for (it = DefSymbol.begin(); it != DefSymbol.end(); it++) {
		if (it->first.size() >= 8)
			cout << it->first << "\t39\t\t" << it->second << endl;
		else
			cout << it->first << "\t\t39\t\t" << it->second << endl;
	}
	cout << "\n==================" << "������" << "==================" << endl;
	cout << "����ֵ\t\t������\t����λ��" << endl;
	for (it = Digit.begin(); it != Digit.end(); it++) {
		cout << it->first << "\t\t40\t\t" << it->second << endl;
	}
}

ostream& operator<<(ostream& output, const Binary& B)//��Binary�����<<����
{
	output << "category: " << B.category << "    index: " << B.index << "    value: " << B.value;
	return output;
}




//�﷨����


//�������

//��Ԫʽ
struct Quadruple {
	Quadruple(string o, string s = "_", string d = "_", string r = "0") {
		opcode = o;
		soperand = s;
		doperand = d;
		result = r;
	}
	Quadruple(){}
	string opcode;//������
	string soperand;//Դ������
	string doperand;//Ŀ�Ĳ�����
	string result;//�������
};
map<string, Quadruple> Quadruples;//��Ԫʽ��
int qid = 150;//��Ԫʽ����Ԫʽ�±�,������
map<string, Quadruple>::iterator itQuad;

int mid = 0;//M~
int nid = 0;//N~





ostream& operator<<(ostream& output, const Quadruple& Q)//��Quadruple�����<<����
{
	output << "opcode: " << Q.opcode << "    soperand: " << Q.soperand << "    doperand: " << Q.doperand << "     result:" << Q.result;
	return output;
}

//�﷨������
typedef struct tree {
	string data;
	tree* next[10] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };
	map<string, vector<string>> Attribute;
}*ptree, tree;
int tid = 1;//T�������±�
vector<string>::iterator itv;//����������
map<string, vector<string>>::iterator itm;//���Ե�����


int ipp;//���ʱ�ǰ�﷨���������±�
void Analysis();
void P();
void A(int pipt);
void B(int pipt);
void D(int pipt);
void X(int pipt);
void X1(int pipt);
void Y(int pipt);
void G(int pipt);
void H(int pipt);
void I(int pipt);
void K(int pipt);
void K1(int pipt);
void L(int pipt);
void E(int pipt);
void E1(int pipt);
void T(int pipt);
void T1(int pipt);
void F(int pipt);
void R(int pipt);
void R1(int pipt);
void Z(int pipt);
void Z1(int pipt);
void Q(int pipt);
void W(int pipt);
void traverse(ptree r) {//ǰ�����
	cout << r->data << "\t\t���ԣ�";
	for (itm = r->Attribute.begin(); itm != r->Attribute.end(); itm++) {
		cout << itm->first<<": ";
		for (itv = itm->second.begin(); itv != itm->second.end(); itv++) {
			cout << *itv << "  ";
		}
	}
	cout << endl;
	
	for (int j = 0; j < 10; j++) {
		if (r->next[j] != NULL) {
			traverse(r->next[j]);
		}
	}
}

ptree root = new tree;//�����ڵ�
ptree p = root;//�������õ��м����



void Analysis() {
	root->data = "P";
	P();
}


//�������ķ�������ʾ���ݹ��½�
void P() {
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�
	if (all[ipp++].category == 1 && all[ipp++].category==100 && all[ipp++].category==101) {//main()
		ptree t1 = new tree;
		t1->data = "main()";
		p->next[pip++] = t1;
		cout << "main()ƥ��ɹ�" << endl;

		ptree t2 = new tree;
		t2->data = "A";
		p->next[pip++] = t2;
		A(pip - 1);
	}
	else {
		cout << "Perror2" << endl;
	}
	cout << "P�������" << endl;
}
void A(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�
	if (all[ipp].category == 105) {//{
		ptree t1 = new tree;
		t1->data = "{";
		p->next[pip++] = t1;
		cout << "{ƥ��ɹ�" << endl;
		ipp++;
		
		ptree t2 = new tree;
		t2->data = "B";
		p->next[pip++] = t2;
		B(pip - 1);
		p = t;

		ptree t3 = new tree;
		t3->data = "G";
		p->next[pip++] = t3;
		G(pip - 1);
		p = t;

		if (all[ipp].category == 106) {//}
			ptree t4 = new tree;
			t4->data = "}";
			p->next[pip++] = t4;
			cout << "}ƥ��ɹ�" << endl;
			ipp++;
		}
		else {
			cout << "Aerror1" << endl;
		}
	}
	else {
		cout << "Aerror2" << endl;
	}
}

void B(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�
	if (all[ipp].category == 2) {//var
		ptree t1 = new tree;
		t1->data = "var";
		p->next[pip++] = t1;
		cout << "varƥ��ɹ�" << endl;
		ipp++;

		ptree t2 = new tree;
		t2->data = "D";
		p->next[pip++] = t2;
		D(pip - 1);
		p = t;
	}
	else {
		cout << "Berror1" << endl;
	}
}

void D(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�

	ptree t1 = new tree;
	t1->data = "X";
	p->next[pip++] = t1;
	X(pip - 1);
	p = t;

	if (all[ipp].category == 103) {//:
		ptree t2 = new tree;
		t2->data = ":";
		p->next[pip++] = t2;
		cout << ":ƥ��ɹ�" << endl;
		ipp++;

		ptree t3 = new tree;
		t3->data = "Y";
		p->next[pip++] = t3;
		Y(pip - 1);
		p = t;

		if (all[ipp].category == 104) {//;
			ptree t4 = new tree;
			t4->data = ";";
			p->next[pip++] = t4;
			cout << ";ƥ��ɹ�" << endl;
			ipp++;

			
			vector<string> v1;
			v1.push_back(p->next[2]->Attribute["type"].back());
			p->Attribute["inherit"] = v1;//D.inherit=Y.type

			vector<string> v2;
			v2.push_back(p->Attribute["inherit"].back());
			p->next[0]->Attribute["type"] = v2;

			if (all[ipp].category == 39 && all[ipp + 1].category == 102) {
				ptree t5 = new tree;
				t5->data = "D";
				p->next[pip++] = t5;
				D(pip - 1);
				p = t;

			}else if (all[ipp].category == 39 && all[ipp + 1].category == 103 && (all[ipp + 2].category == 3 || all[ipp + 2].category == 4)) {
				ptree t5 = new tree;
				t5->data = "D";
				p->next[pip++] = t5;
				D(pip - 1);
				p = t;

			}
		}
		else {
			cout << "Derror1" << endl;
			exit(-1);
		}
	}
	else {
		cout << "Derror2" << endl;
		exit(-1);
	}



}

void X(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�
	if (all[ipp].category == 39) {
		ptree t1 = new tree;
		t1->data = all[ipp].value;
		p->next[pip++] = t1;
		cout <<all[ipp].value<< "ƥ��ɹ�" << endl;

		if (defSymbol(all[ipp].value, true)) {
			cout << all[ipp].value << "�ظ�������" << endl;
			exit(-1);//ֱ���˳�����
		}
		ipp++;

		ptree t2 = new tree;
		t2->data = "X1";
		p->next[pip++] = t2;
		X1(pip - 1);
		p = t;

	}
	else {
		cout << "Xerror1" << endl;
	}
}

void X1(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�
	if (all[ipp].category == 102) {//,
		ptree t1 = new tree;
		t1->data = ",";
		p->next[pip++] = t1;
		cout << ",ƥ��ɹ�" << endl;
		ipp++;

		ptree t2 = new tree;
		t2->data = "X";
		p->next[pip++] = t2;
		X(pip - 1);
		p = t;
	}
}

void Y(int pipt) {
	p = p->next[pipt];
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�

	if (all[ipp].category == 3) {//integer
		ptree t1 = new tree;
		t1->data = "integer";
		p->next[pip++] = t1;
		cout <<"integerƥ��ɹ�" << endl;
		ipp++;
		vector<string> v;
		v.push_back("integer");
		p->Attribute["type"] = v;
		return;
	}
	if (all[ipp].category == 4) {//real
		ptree t1 = new tree;
		t1->data = "real";
		p->next[pip++] = t1;
		cout <<"realƥ��ɹ�" << endl;
		ipp++;
		vector<string> v;
		v.push_back("real");
		p->Attribute["type"] = v;
		return;
	}
	else {
		cout << "Yerror" << endl;
		exit(-1);
	}
}

void G(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�

	ptree t1 = new tree;
	t1->data = "H";
	p->next[pip++] = t1;
	H(pip - 1);
	p = t;

	
	if (all[ipp].category == 104) {//;
		ptree t2 = new tree;
		t2->data = ";";
		p->next[pip++] = t2;
		cout <<";ƥ��ɹ�" << endl;
		ipp++;

		ptree t3 = new tree;
		t3->data = "M" + to_string(mid++);
		p->next[pip++] = t3;
		cout << t3->data << "��ӳɹ�" << endl;
		vector<string> v1;
		v1.push_back(to_string(qid));
		p->next[2]->Attribute["quad"] = v1;//M.quadΪ��һ�����ŵ���һ��ֵ

		ptree t4 = new tree;
		t4->data = "G";
		p->next[pip++] = t4;
		G(pip - 1);
		p = t;

		vector<string> v2;
		v2.push_back(p->next[2]->Attribute["quad"].back());
		p->next[0]->Attribute["next"] = v2;

		p->Attribute["next"] = p->next[3]->Attribute["next"];//��G.next=��G.next

	}
	else {

		p->Attribute["next"] = p->next[0]->Attribute["next"];//G.next=H.next

	}
}


void H(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�
	if (all[ipp].category == 39) {
		ptree t1 = new tree;
		t1->data = "I";
		p->next[pip++] = t1;
		I(pip - 1);
		p = t;
		
		p->Attribute["next"] = p->next[0]->Attribute["next"];
	}
	else if (all[ipp].category == 9) {//if
		ptree t1 = new tree;
		t1->data = "K";
		p->next[pip++] = t1;
		K(pip - 1);
		p = t;

		p->Attribute["next"] = p->next[0]->Attribute["next"];
	}
	else if (all[ipp].category == 7) {//while
		ptree t1 = new tree;
		t1->data = "L";
		p->next[pip++] = t1;
		L(pip - 1);
		p = t;

		p->Attribute["next"] = p->next[0]->Attribute["next"];
	}
	else {
		cout << "Herror" << endl;
	}
}

void I(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�
	//if (all[ipp].category == 39){
	if (defSymbol(all[ipp].value,false)) {
		ptree t1 = new tree;
		t1->data = all[ipp].value;
		p->next[pip++] = t1;
		cout << all[ipp].value << "ƥ��ɹ�" << endl;
		ipp++;
		if (all[ipp].category == 50) {//:=
			ptree t2 = new tree;
			t2->data = ":=";
			p->next[pip++] = t2;
			cout << ":=ƥ��ɹ�" << endl;
			ipp++;

			ptree t3 = new tree;
			t3->data = "E";
			p->next[pip++] = t3;
			E(pip-1);
			p = t;
		}
	}
	else {
		cout << "Ierror:û�ж���˱�ʶ��" << endl;
		return;
	}

	Quadruple quad( p->next[1]->data, 
		p->next[2]->Attribute.find("place")->second.back(),
		"_", 
		p->next[0]->data);
	Quadruples[to_string(qid++)] = quad;

	vector<string> v;
	p->Attribute["next"] = v;

} 

void K(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�
	if (all[ipp].category == 9) {//if
		ptree t1 = new tree;
		t1->data = "if";
		p->next[pip++] = t1;
		cout << "ifƥ��ɹ�" << endl;
		ipp++;

		ptree t2 = new tree;
		t2->data = "R";
		p->next[pip++] = t2;
		R(pip - 1);
		p = t;

		if (all[ipp].category == 10) {//then
			ptree t3 = new tree;
			t3->data = "then";
			p->next[pip++] = t3;
			cout << "thenƥ��ɹ�" << endl;
			ipp++;

			ptree t4 = new tree;
			t4->data = "M" + to_string(mid++);
			p->next[pip++] = t4;
			cout << t4->data << "��ӳɹ�" << endl;
			vector<string> v1;
			v1.push_back(to_string(qid));
			p->next[3]->Attribute["quad"] = v1;//M.quadΪ��һ�����ŵ���һ��ֵ

			ptree t5 = new tree;
			t5->data = "H";
			p->next[pip++] = t5;
			H(pip - 1);
			p = t;

			if (all[ipp].category == 11) {//else
				ptree t6 = new tree;
				t6->data = "K1";
				p->next[pip++] = t6;
				K1(pip - 1);
				p = t;

				//��else�Ĳ���
				//����M1.quad
				itQuad = Quadruples.find(p->next[1]->Attribute["true"].back());//R��true��Ԫ��
				itQuad->second.result = p->next[3]->Attribute["quad"].back();//M1.quad����

				//����M2.quad
				itQuad = Quadruples.find(p->next[1]->Attribute["false"].back());//R��false��Ԫʽ
				itQuad->second.result = p->next[5]->next[2]->Attribute["quad"].back();//M2.quad����

				//K.next
				vector<string> v;
				//H1��next
				vector<string> vt1 = p->next[4]->Attribute["next"];
				for (itv = vt1.begin(); itv != vt1.end(); itv++) {
					v.push_back(*itv);
				}
				//N��next
				v.push_back(p->next[5]->next[0]->Attribute["next"].back());
				//H2��next
				vector<string> vt2 = p->next[5]->next[3]->Attribute["next"];
				for (itv = vt2.begin(); itv != vt2.end(); itv++) {
					v.push_back(*itv);
				}
				p->Attribute["next"] = v;

			}
			else {
				//����
				itQuad = Quadruples.find(p->next[1]->Attribute["true"].back());//RΪtrue��
				itQuad->second.result = p->next[3]->Attribute["quad"].back();//M.quad����

				vector<string> v;
				vector<string> vt1 = p->next[1]->Attribute["false"];//RΪfalse����Ԫ��
				for (itv = vt1.begin(); itv != vt1.end(); itv++) {
					v.push_back(*itv);
				}
				vector<string> vt2 = p->next[4]->Attribute["next"];//H��next
				for (itv = vt2.begin(); itv != vt2.end(); itv++) {
					v.push_back(*itv);
				}
				p->Attribute["next"] = v; //K.next����

			}
		}
		else {
			cout << "Kerror1:û��then" << endl;

		}
	}
	else {
		cout << "Kerror2" << endl;
	}
}

void K1(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�
	
	if (all[ipp].category == 11) {//else
								  
		ptree t1 = new tree;
		t1->data = "N" + to_string(nid++);
		p->next[pip++] = t1;
		cout << t1->data << "��ӳɹ�" << endl;
		vector<string> v1;
		v1.push_back(to_string(qid));
		p->next[0]->Attribute["next"] = v1;//N.next����¼��������ת������ֱ������H2
		//��������ת���
		Quadruple quad("J");
		Quadruples[to_string(qid++)] = quad;

		ptree t2 = new tree;
		t2->data = "else";
		p->next[pip++] = t2;
		cout << "elseƥ��ɹ�" << endl;
		ipp++;

		ptree t3 = new tree;
		t3->data = "M" + to_string(mid++);
		p->next[pip++] = t3;
		cout << t3->data << "��ӳɹ�" << endl;
		vector<string> v2;
		v2.push_back(to_string(qid));
		p->next[2]->Attribute["quad"] = v2;//M.quadΪ��һ�����ŵ���һ��ֵ

		ptree t4 = new tree;
		t4->data = "H";
		p->next[pip++] = t4;
		H(pip - 1);
		p = t;
	}
	else {
		cout << "K1error" << endl;
	}
}

void L(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�

	if (all[ipp].category == 7) {//while
		ptree t1 = new tree;
		t1->data = "while";
		p->next[pip++] = t1;
		cout <<"whileƥ��ɹ�" << endl;
		ipp++;

		ptree t2 = new tree;
		t2->data = "M" + to_string(mid++);
		p->next[pip++] = t2;
		cout << t2->data << "��ӳɹ�" << endl;
		vector<string> v1;
		v1.push_back(to_string(qid));
		p->next[1]->Attribute["quad"] = v1;//M1.quadΪ��һ�����ŵ���һ��ֵ
		
		

		ptree t3 = new tree;
		t3->data = "R";
		p->next[pip++] = t3;
		R(pip - 1);
		p = t;

		if (all[ipp].category == 8) {//do
			ptree t4 = new tree;
			t4->data = "do";
			p->next[pip++] = t4;
			cout << "doƥ��ɹ�" << endl;
			ipp++;

			ptree t5 = new tree;
			t5->data = "M" + to_string(mid++);
			p->next[pip++] = t5;
			cout << t5->data << "��ӳɹ�" << endl;
			vector<string> v2;
			v2.push_back(to_string(qid));
			p->next[4]->Attribute["quad"] = v2;//M2.quadΪ��һ�����ŵ���һ��ֵ

			ptree t6 = new tree;
			t6->data = "H";
			p->next[pip++] = t6;
			H(pip - 1);
			p = t;

			//RΪfalseʱ
			p->Attribute["next"] = p->next[2]->Attribute["false"];

			//����
			itQuad = Quadruples.find(p->next[2]->Attribute["true"].back());//RΪtrue����Ԫ�������
			itQuad->second.result = p->next[4]->Attribute["quad"].back();//M2.quadֵ����

			//�����Ԫʽ,��������ת
			Quadruple quad("J", "_", "_", p->next[1]->Attribute["quad"].back());//emit("J","_","_",M1.quad)
			Quadruples[to_string(qid++)] = quad;

		}
		else {
			cout << "Lerror:û��do" << endl;
			exit(-1);
		}
	}
}

void E(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�
	ptree t1 = new tree;
	t1->data = "T";
	p->next[pip++] = t1;
	T(pip - 1);
	p = t;

	ptree t2 = new tree;
	t2->data = "E1";
	p->next[pip++] = t2;
	E1(pip - 1);
	p = t;

	//E1���ӽڵ�Ϊ��
	if (p->next[1]->next[0] == NULL) {
		p->Attribute["place"] = p->next[0]->Attribute["place"];
	}
	else {//E1���ӽڵ㲻Ϊ��
		vector<string> v;
		v.push_back("T" + to_string(tid++));
		p->Attribute["place"] = v;
		//��Ԫʽ
		Quadruple quad(p->next[1]->next[0]->data, 
			p->next[0]->Attribute["place"].back(), 
			p->next[1]->Attribute["place"].back(), 
			p->Attribute["place"].back());

		Quadruples[to_string(qid++)] = quad;
	}


}

void E1(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�
	if (all[ipp].category == 51) {//+
		ptree t1 = new tree;
		t1->data = "+";
		p->next[pip++] = t1;
		cout <<"+ƥ��ɹ�" << endl;
		ipp++;

		ptree t2 = new tree;
		t2->data = "T";
		p->next[pip++] = t2;
		T(pip - 1);
		p = t;

		ptree t3 = new tree;
		t3->data = "E1";
		p->next[pip++] = t3;
		E1(pip - 1);
		p = t;


		if (p->next[2]->next[0] == NULL) {//E1�ӽڵ�Ϊ��
			p->Attribute["place"] = p->next[1]->Attribute["place"];
		}
		else if(p->next[2]->next[2]->next[0]==NULL) {//���´���E1�ӽڵ�Ϊ��
			vector<string> v;
			v.push_back("T" + to_string(tid++));
			p->Attribute["place"] = v;//����place����
			//�±߸���Ԫʽ
			//������E1��+������T��place������E1��T��place���м����T~��//s:��T,d:��T
			Quadruple quad(p->next[2]->next[0]->data,
				p->next[1]->Attribute["place"].back(),
				p->next[2]->next[1]->Attribute["place"].back(),
				p->Attribute["place"].back());
			Quadruples[to_string(qid++)] = quad;
		}
		else {
			vector<string> v;
			v.push_back("T" + to_string(tid++));
			p->Attribute["place"] = v;//����place����
			//�±߸���Ԫʽ
			//������E1��+������T��place������E1��place���м����T~��//s:��T,d:��T
			Quadruple quad(p->next[2]->next[0]->data,
				p->next[1]->Attribute["place"].back(),
				p->next[2]->Attribute["place"].back(),
				p->Attribute["place"].back());
			Quadruples[to_string(qid++)] = quad;
		}
	}
	else if (all[ipp].category == 52) {//-
		ptree t1 = new tree;
		t1->data = "-";
		p->next[pip++] = t1;
		cout <<"-ƥ��ɹ�" << endl;
		ipp++;

		ptree t2 = new tree;
		t2->data = "T";
		p->next[pip++] = t2;
		T(pip - 1);
		p = t;

		ptree t3 = new tree;
		t3->data = "E1";
		p->next[pip++] = t3;
		E1(pip - 1);
		p = t;

		if (p->next[2]->next[0] == NULL) {//E1�ӽڵ�Ϊ��
			p->Attribute["place"] = p->next[1]->Attribute["place"];
		}
		else if(p->next[2]->next[2]->next[0]==NULL) {//���´���E1�ӽڵ�Ϊ��
			vector<string> v;
			v.push_back("T" + to_string(tid++));
			p->Attribute["place"] = v ;//����place����
			//�±߸���Ԫʽ
			//������E1��-������T��place������E1��T��place���м����T~��//s:��T,d:��T
			Quadruple quad(p->next[2]->next[0]->data,
				p->next[1]->Attribute["place"].back(),
				p->next[2]->next[1]->Attribute["place"].back(),
				p->Attribute["place"].back());
			Quadruples[to_string(qid++)] = quad;
		}
		else {
			vector<string> v;
			v.push_back("T" + to_string(tid++));
			p->Attribute["place"] = v;//����place����
			//�±߸���Ԫʽ
			//������E1��-������T��place������E1��place���м����T~��//s:��T,d:��T
			Quadruple quad(p->next[2]->next[0]->data,
				p->next[1]->Attribute["place"].back(),
				p->next[2]->Attribute["place"].back(),
				p->Attribute["place"].back());
			Quadruples[to_string(qid++)] = quad;
		}
	}
}

void T(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�

	ptree t1 = new tree;
	t1->data = "F";
	p->next[pip++] = t1;
	F(pip - 1);
	p = t;

	ptree t2 = new tree;
	t2->data = "T1";
	p->next[pip++] = t2;
	T1(pip - 1);
	p = t;


	//����T1���ӽڵ�Ϊ�յ����
	if (p->next[1]->next[0] == NULL) {
		p->Attribute["place"] = p->next[0]->Attribute["place"];
	}
	else {
		//palce����ΪF���F�ҵ��м����T*
		vector<string> v;
		v.push_back("T" + to_string(tid++));
		p->Attribute["place"] = v;
		//�±߸���Ԫʽ
		Quadruple quad(p->next[1]->next[0]->data, 
			p->next[0]->Attribute["place"].back(), 
			p->next[1]->Attribute["place"].back(), //T1�����
			p->Attribute["place"].back());
		
		Quadruples[to_string(qid++)] = quad;//��ӽ���Ԫʽ��
	}

	
}

void T1(int pipt) {//����T1�ӽڵ�Ϊ�գ�������ʽ�ˣ�place���Ի��������
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�
	if (all[ipp].category == 53) {// *
		ptree t1 = new tree;
		t1->data = "*";
		p->next[pip++] = t1;
		cout << "*ƥ��ɹ�" << endl;
		ipp++;

		ptree t2 = new tree;
		t2->data = "F";
		p->next[pip++] = t2;
		F(pip - 1);
		p = t;

		ptree t3 = new tree;
		t3->data = "T1";
		p->next[pip++] = t3;
		T1(pip - 1);
		p = t;

		if (p->next[2]->next[0] == NULL) {//T1�ӽڵ�Ϊ��
			p->Attribute["place"] = p->next[1]->Attribute["place"];
		}
		else if(p->next[2]->next[2]->next[0] == NULL) {//���´���T1�ӽڵ�Ϊ��
			vector<string> v;
			v.push_back("T" + to_string(tid++));
			p->Attribute["place"] = v;//����place����
			//�±߸���Ԫʽ
			//������T1��*������F��place������T1��F��place���м����T~��//s:��F,d:��F
			Quadruple quad(p->next[2]->next[0]->data, 
				p->next[1]->Attribute["place"].back(), 
				p->next[2]->next[1]->Attribute["place"].back(), 
				p->Attribute["place"].back());
			Quadruples[to_string(qid++)] = quad;
		}
		else {
			vector<string> v;
			v.push_back("T" + to_string(tid++));
			p->Attribute["place"] = v;//����place����
			//�±߸���Ԫʽ
			//������T1��*������F��place������T1��place���м����T~��//s:��F,d:��F
			Quadruple quad(p->next[2]->next[0]->data,
				p->next[1]->Attribute["place"].back(),
				p->next[2]->Attribute["place"].back(),
				p->Attribute["place"].back());
			Quadruples[to_string(qid++)] = quad;
		}

	}
	else if (all[ipp].category == 54) {// /
		ptree t1 = new tree;
		t1->data = "/";
		p->next[pip++] = t1;
		cout << "/ƥ��ɹ�" << endl;
		ipp++;

		ptree t2 = new tree;
		t2->data = "F";
		p->next[pip++] = t2;
		F(pip - 1);
		p = t;


		ptree t3 = new tree;
		t3->data = "T1";
		p->next[pip++] = t3;
		T1(pip - 1);
		p = t;

		if (p->next[2]->next[0] == NULL) {//T1�ӽڵ�Ϊ��
			p->Attribute["place"] = p->next[1]->Attribute["place"];
		}
		else if(p->next[2]->next[2]->next[0] == NULL){//���´���T1�ڵ�Ϊ��
			vector<string> v;
			v.push_back("T" + to_string(tid++));
			p->Attribute["place"] = v;//����place����
			//�±߸���Ԫʽ
			//������T1��/������F��place������T1��F��place���м����T~��//s:��F,d:��F
			Quadruple quad(p->next[2]->next[0]->data,
				p->next[1]->Attribute["place"].back(),
				p->next[2]->next[1]->Attribute["place"].back(),
				p->Attribute["place"].back());
			Quadruples[to_string(qid++)] = quad;
		}
		else {
			vector<string> v;
			v.push_back("T" + to_string(tid++));
			p->Attribute["place"] = v;//����place����
			//�±߸���Ԫʽ
			//������T1��/������F��place������T1��place���м����T~��//s:��F,d:��F
			Quadruple quad(p->next[2]->next[0]->data,
				p->next[1]->Attribute["place"].back(),
				p->next[2]->Attribute["place"].back(),
				p->Attribute["place"].back());
			Quadruples[to_string(qid++)] = quad;
		}
	}
}

void F(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�
	
	if (defSymbol(all[ipp].value, false) || all[ipp].category == 40) {//ƥ���ʶ������
		ptree t1 = new tree;//�����ڵ�
		t1->data = all[ipp].value;
		p->next[pip++] = t1;
		cout << all[ipp].value << "ƥ��ɹ�" << endl;
		vector<string> v;
		v.push_back(all[ipp].value);
		p->Attribute["place"] = v;//����place����

		ipp++;

	}else if (all[ipp].category == 100) {//(
		ptree t1 = new tree;
		t1->data = "(";
		p->next[pip++] = t1;
		cout << "(ƥ��ɹ�" << endl;
		ipp++;

		ptree t2 = new tree;
		t2->data = "E";
		p->next[pip++] = t2;
		E(pip - 1);
		p = t;
		p->Attribute["place"] = p->next[pip - 1]->Attribute["place"];


		if (all[ipp].category == 101) {//)
			ptree t3 = new tree;
			t3->data = ")";
			p->next[pip++] = t3;
			cout << ")ƥ��ɹ�" << endl;
			ipp++;
		}
		else {
			cout << "Ferror1:û�� ) " << endl;
			return;
		}

	}
	else {
		cout << "Ferror2��û�ж���˱�ʶ��" << endl;
	}
}

void R(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�

	ptree t1 = new tree;
	t1->data = "Z";
	p->next[pip++] = t1;
	Z(pip - 1);
	p = t;

	ptree t2 = new tree;
	t2->data = "R1";
	p->next[pip++] = t2;
	R1(pip - 1);
	p = t;

	if (p->next[1]->next[0] == NULL) {//�˽ڵ��R1�ӽڵ�nextΪ��
		p->Attribute["true"] = p->next[0]->Attribute["true"];
		p->Attribute["false"] = p->next[0]->Attribute["false"];

	}
	else if(p->next[1]->next[3]->next[0] == NULL){//�˽ڵ����R1�ӽڵ�nextΪ��

		//R.false�����
		p->Attribute["false"] = p->next[1]->next[2]->Attribute["false"];//R.false=Z2.false

		//R.true�����
		vector<string> v2;
		vector<string> vt1 = p->next[0]->Attribute["true"];//Z1��true��ת����������
		for (itv = vt1.begin(); itv != vt1.end(); itv++) {
			v2.push_back(*itv);
		}
		vector<string> vt2 = p->next[1]->next[2]->Attribute["true"];//Z2��true��ת����������	
		for (itv = vt2.begin(); itv != vt2.end(); itv++) {
			v2.push_back(*itv);
		}
		p->Attribute["true"] = v2;//����

		//����
		itQuad = Quadruples.find(p->next[0]->Attribute["false"].back());//Z1��false����Ԫʽ
		itQuad->second.result = p->next[1]->next[1]->Attribute["quad"].back();//M��quad����ֵ���Q1��true��result

	}
	else {
		//R.false�����
		p->Attribute["false"] = p->next[1]->Attribute["false"];//R.false=R1.false

		//R.true�����
		vector<string> v2;
		vector<string> vt1 = p->next[0]->Attribute["true"]; //Z1��true��ת����������
		for (itv = vt1.begin(); itv != vt1.end(); itv++) {
			v2.push_back(*itv);
		}
		vector<string> vt2 = p->next[1]->Attribute["true"]; //R1��true��ת����������
		for (itv = vt2.begin(); itv != vt2.end(); itv++) {
			v2.push_back(*itv);
		}
		p->Attribute["true"] = v2;

		//����
		itQuad = Quadruples.find(p->next[0]->Attribute["false"].back());//Z1��false����Ԫʽ
		itQuad->second.result = p->next[1]->next[1]->Attribute["quad"].back();//M��quad����ֵ���Q1��true��result

	}

}

void R1(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�
	if (all[ipp].category == 12) {//or
		ptree t1 = new tree;
		t1->data = "or";
		p->next[pip++] = t1;
		cout << "orƥ��ɹ�" << endl;
		ipp++;

		ptree t2 = new tree;
		t2->data = "M" + to_string(mid++);
		p->next[pip++] = t2;
		cout << t2->data << "��ӳɹ�" << endl;
		vector<string> v1;
		v1.push_back(to_string(qid));
		p->next[1]->Attribute["quad"] = v1;//M.quadΪ��һ�����ŵ���һ��ֵ

		ptree t3 = new tree;
		t3->data = "Z";
		p->next[pip++] = t3;
		Z(pip - 1);
		p = t;

		ptree t4 = new tree;
		t4->data = "R1";
		p->next[pip++] = t4;
		R1(pip - 1);
		p = t;

		if (p->next[3]->next[0] == NULL) {}//�˽ڵ���R1�ӽڵ�Ϊ��
		else if (p->next[3]->next[3]->next[0] == NULL) {//���´���R1�ӽڵ�Ϊ��

			//R1.false�����
			p->Attribute["false"] = p->next[3]->next[2]->Attribute["false"];//R1.false=Z2.false

			//R1.true�����
			vector<string> v2;
			vector<string> vt1 = p->next[2]->Attribute["true"];//Z1��true��ת����������
			for (itv = vt1.begin(); itv != vt1.end(); itv++) {
				v2.push_back(*itv);
			}
			vector<string> vt2 = p->next[3]->next[2]->Attribute["true"];//Z2��true��ת����������	
			for (itv = vt2.begin(); itv != vt2.end(); itv++) {
				v2.push_back(*itv);
			}
			p->Attribute["true"] = v2;

			//����
			itQuad = Quadruples.find(p->next[2]->Attribute["false"].back());//Z1��false����Ԫʽ
			itQuad->second.result = p->next[3]->next[1]->Attribute["quad"].back();//M��quad����ֵ���Q1��true��result


		}
		else {//���´���R1�ӽڵ㲻Ϊ��

			//R1.false�����
			p->Attribute["false"] = p->next[3]->Attribute["false"];//��R1.false=��R1.false

			//R1.true�����
			vector<string> v2;
			vector<string> vt1 = p->next[2]->Attribute["true"]; //Z1��true��ת����������
			for (itv = vt1.begin(); itv != vt1.end(); itv++) {
				v2.push_back(*itv);
			}
			vector<string> vt2 = p->next[3]->Attribute["true"]; //��R1��true��ת����������
			for (itv = vt2.begin(); itv != vt2.end(); itv++) {
				v2.push_back(*itv);
			}
			p->Attribute["true"] = v2;

			//����
			itQuad = Quadruples.find(p->next[2]->Attribute["false"].back());//Z1��false����Ԫʽ
			itQuad->second.result = p->next[3]->next[1]->Attribute["quad"].back();//M��quad����ֵ���Q1��true��result

		}

	}
}

void Z(int pipt) {//��true��false����
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�

	ptree t1 = new tree;
	t1->data = "Q";
	p->next[pip++] = t1;
	Q(pip - 1);
	p = t;

	ptree t2 = new tree;
	t2->data = "Z1";
	p->next[pip++] = t2;
	Z1(pip - 1);
	p = t;

	if (p->next[1]->next[0] == NULL) {//��Z�ڵ���Z1�ӽڵ�nextΪ��
		p->Attribute["true"] = p->next[0]->Attribute["true"];
		p->Attribute["false"] = p->next[0]->Attribute["false"];
	}
	else if(p->next[1]->next[3]->next[0]==NULL){//��Z�ڵ��´���Z1�ӽڵ�nextΪ��
		
		//Z.true�����
		p->Attribute["true"] = p->next[1]->next[2]->Attribute["true"];//Z.true=Q2.true

		//Z.false�����
		vector<string> v1;
		v1.push_back(p->next[0]->Attribute["false"].back());//Q1��false��ת������
		v1.push_back(p->next[1]->next[2]->Attribute["false"].back());//Q2��false��ת������
		p->Attribute["false"] = v1;

		//����
		itQuad = Quadruples.find(p->next[0]->Attribute["true"].back());//Q1��true����Ԫʽ
		itQuad->second.result = p->next[1]->next[1]->Attribute["quad"].back();//M��quad����ֵ���Q1��true��result

	}
	else {
		//Z.true�����
		p->Attribute["true"] = p->next[1]->Attribute["true"];//Z.true=Z1.true

		//Z.false�����
		vector<string> v2;
		v2.push_back(p->next[0]->Attribute["false"].back());//Q1��false��ת������
		vector<string> vt = p->next[1]->Attribute["false"]; //Z1��false��ת����������
		for (itv = vt.begin(); itv != vt.end(); itv++) {
			v2.push_back(*itv);
		}
		p->Attribute["false"] = v2;

		//����
		itQuad = Quadruples.find(p->next[0]->Attribute["true"].back());//Q1��true����Ԫʽ
		itQuad->second.result = p->next[1]->next[1]->Attribute["quad"].back();//M��quad����ֵ���Q1��true��result

	}

}

void Z1(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�
	if (all[ipp].category == 13) {//and
		ptree t1 = new tree;
		t1->data = "and";
		p->next[pip++] = t1;
		cout << "andƥ��ɹ�" << endl;
		ipp++;

		ptree t2 = new tree;
		t2->data = "M" + to_string(mid++);
		p->next[pip++] = t2;
		cout << t2->data << "��ӳɹ�" << endl; 
		vector<string> v1;
		v1.push_back(to_string(qid));
		p->next[1]->Attribute["quad"] = v1;//M.quadΪ��һ�����ŵ���һ��ֵ

		ptree t3 = new tree;
		t3->data = "Q";
		p->next[pip++] = t3;
		Q(pip - 1);
		p = t;

		ptree t4 = new tree;
		t4->data = "Z1";
		p->next[pip++] = t4;
		Z1(pip - 1);
		p = t;


		
		if (p->next[3]->next[0] == NULL) {}//�˽ڵ���Z1�ӽڵ�Ϊ��}
		else if(p->next[3]->next[3]->next[0]==NULL){//���´���Z1�ӽڵ�Ϊ��
			
			//Z1.true�����
			p->Attribute["true"] = p->next[3]->next[2]->Attribute["true"];//Z1.true=Q2.true

			//Z1.false�����
			//����,������Ԫʽ��ֵ��������
			//itQuad = Quadruples.find(p->next[3]->next[2]->Attribute["false"].back());//Q2��false����Ԫʽ
			//itQuad->second.result = p->next[2]->Attribute["false"];//Q1��false����Ԫʽ�����Q2��false����
			vector<string> v2;
			v2.push_back(p->next[2]->Attribute["false"].back());//Q1��false��ת������
			v2.push_back(p->next[3]->next[2]->Attribute["false"].back());//Q2��false��ת������
			p->Attribute["false"] = v2;
			
			//����ͽ���������Ԫʽ��resultֵ��ͻ������ѡ��ֻ�����Ԫʽ
			itQuad = Quadruples.find(p->next[2]->Attribute["true"].back());//Q1��true����Ԫʽ
			itQuad->second.result = p->next[3]->next[1]->Attribute["quad"].back();//M��quad����ֵ���Q1��true��result
			

		}
		else {//���´���Z1�ӽڵ㲻Ϊ��
			
			//Z1.true�����
			p->Attribute["true"] = p->next[3]->Attribute["true"];//��Z1.true=��Z1.true

			//Z1.false�����
			vector<string> v2;
			v2.push_back(p->next[2]->Attribute["false"].back());//Q1��false��ת������
			vector<string> vt = p->next[3]->Attribute["false"]; //��Z1��false��ת����������
			for (itv = vt.begin(); itv != vt.end(); itv++) {
				v2.push_back(*itv);
			}
			p->Attribute["false"] = v2;

			//����
			itQuad = Quadruples.find(p->next[2]->Attribute["true"].back());//Q1��true����Ԫʽ
			itQuad->second.result = p->next[3]->next[1]->Attribute["quad"].back();//M��quad����ֵ���Q1��true��result

		}


	}
}

void Q(int pipt) {
	p = p->next[pipt];
	ptree t = p;
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�

	if (defSymbol(all[ipp].value, false) || all[ipp].category==40) {
		ptree t1 = new tree;
		t1->data = all[ipp].value;
		p->next[pip++] = t1;
		cout << all[ipp].value << "ƥ��ɹ�" << endl;
		ipp++;

		ptree t2 = new tree;
		t2->data = "W";
		p->next[pip++] = t2;
		W(pip - 1);
		p = t;

		if (defSymbol(all[ipp].value, false) || all[ipp].category == 40) {
			ptree t3 = new tree;
			t3->data = all[ipp].value;
			p->next[pip++] = t3;
			cout << all[ipp].value << "ƥ��ɹ�" << endl;
			ipp++;
		}
		else {
			cout << "Qerror1:û�ж���˱�ʶ��" << endl;
			return;
		}

		Quadruple quad1("J" + p->next[1]->next[0]->data, p->next[0]->data, p->next[2]->data);//���ڱȽϵĲ������ӵ���Ԫʽ
		Quadruples[to_string(qid++)] = quad1;

		Quadruple quad2("J");
		Quadruples[to_string(qid++)] = quad2;  

		vector<string> v1;
		v1.push_back(to_string(qid - 2));
		p->Attribute["true"] = v1;
		vector<string> v2;
		v2.push_back(to_string(qid - 1));
		p->Attribute["false"] = v2;

	}else
	if (all[ipp].category == 14) {//not
		ptree t1 = new tree;
		t1->data = "not";
		p->next[pip++] = t1;
		cout << "notƥ��ɹ�" << endl;
		ipp++;

		ptree t2 = new tree;
		t2->data = "Q";
		p->next[pip++] = t2;
		Q(pip - 1);
		p = t;

		p->Attribute["true"] = p->next[1]->Attribute["false"];
		p->Attribute["false"] = p->next[1]->Attribute["true"];
	}
	else {
		cout << "Qerror2:û�ж���˱�ʶ��" << endl;
		return;
	}
}

void W(int pipt) {
	p = p->next[pipt];
	int pip = 0;//���ڵ��µ�ֱ���ӽڵ��±�,��������ӽڵ�
	if (all[ipp].category == 55) {//<
		ptree t1 = new tree;
		t1->data = "<";
		p->next[pip++] = t1;
		cout << "<ƥ��ɹ�" << endl;
		ipp++;
		return;
	}else
	if (all[ipp].category == 56) {//<=
		ptree t1 = new tree;
		t1->data = "<=";
		p->next[pip++] = t1;
		cout << "<=ƥ��ɹ�" << endl;
		ipp++;
		return;
	}else
	if (all[ipp].category == 57) {//>
		ptree t1 = new tree;
		t1->data = ">";
		p->next[pip++] = t1;
		cout << ">ƥ��ɹ�" << endl;
		ipp++;
		return;
	}else
	if (all[ipp].category == 58) {//>=
		ptree t1 = new tree;
		t1->data = ">=";
		p->next[pip++] = t1;
		cout << ">=ƥ��ɹ�" << endl;
		ipp++;
		return;
	}else
	if (all[ipp].category == 59) {//==
		ptree t1 = new tree;
		t1->data = "==";
		p->next[pip++] = t1;
		cout << "==ƥ��ɹ�" << endl;
		ipp++;
		return;
	}else
	if (all[ipp].category == 60) {//!=
		ptree t1 = new tree;
		t1->data = "!=";
		p->next[pip++] = t1;
		cout << "!=ƥ��ɹ�" << endl;
		ipp++;
		return;
	}
	else {
		cout << "Werror"<< endl;
	}
}


//Ŀ���������
map<string, string> Rvalue;//�Ĵ�����������///ʲô�Ĵ����洢ʲô����//AX:T1
map<string, string>::iterator itReg;
map<string, string> Code;//����MOV  ֵ��AX,X|| JG A' 
map<string, string>::iterator itCode;
int cid = 0;
map<string, string> Avalue;//������ַ��������///ʲô������ʲôλ���д洢//T1:AX
map<string, string>::iterator itAv;

/// <summary>
/// ����δʹ�üĴ���
/// </summary>
/// <returns>���ؼĴ�����</returns>
string reEmptyReg() {
	for (itReg = Rvalue.begin(); itReg != Rvalue.end(); itReg++) {
		if (itReg->second == "") {
			return itReg->first;
		}
	}
}

void rstReg(string T) {//���洢ָ��Ԫ�صļĴ����ÿ�
	for (itReg = Rvalue.begin(); itReg != Rvalue.end(); itReg++) {
		if (itReg->second == T) {
			itReg->second = "";
			return;
		}
	}
}


void generateCode() {//����Ŀ�����
	Rvalue["AX"] = "";//��ʼ���Ĵ���
	Rvalue["BX"] = "";
	string reg;

	for (itQuad = Quadruples.begin(); itQuad != Quadruples.end(); itQuad++) {
		if (itQuad->second.opcode == "+") {
			/// ��   opcode: +    soperand: a    doperand: b     result:T1
			/// ��   opcode: +    soperand: T1    doperand: b     result:T2
			/// ��   opcode: +    soperand: a    doperand: T2     result:T3
			/// ��   opcode: +    soperand: T3    doperand: T4     result:T5
			 
			if (itQuad->second.opcode[0] == 'T') {//�ڢ�
				//��opcode: +    soperand: T3    doperand: T4     result:T5
				if (itQuad->second.doperand[0] == 'T') {

				}
				else {//��opcode: +    soperand: T1    doperand: b     result:T2

				}


			}
			else {//�٢�
				//��opcode: +    soperand: a    doperand: T2     result:T3
				if (itQuad->second.doperand[0] == 'T') {
					

				}
				else {//��opcode: +    soperand: a    doperand: b     result:T1
					reg = reEmptyReg();
					if (reg != "") {//��δ��ʹ�õļĴ���
						//a����reg�Ĵ�����//����MOV XX,a 
						Rvalue[reg] = itQuad->second.soperand;
						Code[to_string(cid++)] = "MOV "+reg + "," + itQuad->second.soperand;

						//���//����ADD XX��b
						Code[to_string(cid++)] = "ADD "+ reg + "," + itQuad->second.doperand;

						//result���T1����XX�Ĵ����У��޸�Rvalue,Avalue
						Rvalue[reg] = itQuad->second.result;
						Avalue[itQuad->second.result] = reg;

					}
					else {//�Ѿ�û��δ��ʹ�õļĴ����ˣ������м����������Զ�Ĳ��õ�
						int far = 150;
						string farT;
						for (itReg = Rvalue.begin(); itReg != Rvalue.end(); itReg++) {
							for (itQuad = Quadruples.begin(); itQuad != Quadruples.end(); itQuad++) {
								int t = atoi(itQuad->first.c_str());//�ַ���ת����
								if (itReg->second == itQuad->second.soperand) {
									if (far < t) { 
										far = t; //���¾���
										farT = itReg->second;//��¼��Զ�ı���
									}
								}
								if (itReg->second == itQuad->second.doperand) {
									if (far < t) {
										far = t;
										farT = itReg->second;
									}
								}
							}
						}
						//XX[farT]�ÿ�
						rstReg(farT);
						//���»�ȡ����reg
						reg = reEmptyReg();
						
						//Avalue��ɾ��Tx��XX�Ĵ�����
						Avalue.erase(farT);

						//Avalue�����Tx��Tx������
						Avalue[farT] = farT;

						//����MOV Tx,XX
						Code[to_string(cid++)] = "MOV "+farT + "," + reg;

						//a����reg�Ĵ�����//����MOV XX,a 
						Rvalue[reg] = itQuad->second.soperand;
						
						Code[to_string(cid++)] = "MOV "+reg + "," + itQuad->second.soperand;

						//���//����ADD XX��b
						Code[to_string(cid++)] = "ADD "+ reg + "," + itQuad->second.doperand;

						//result���T1����XX�Ĵ����У��޸�Rvalue,Avalue
						Rvalue[reg] = itQuad->second.result;
						Avalue[itQuad->second.result] = reg;

					}
				}
			}
		}
		if (itQuad->second.opcode == "-") {


		}
		if (itQuad->second.opcode == "*") {


		}
		if (itQuad->second.opcode == "/") {


		}
		if (itQuad->second.opcode == "J") {


		}
		if (itQuad->second.opcode == "J<") {


		}
		if (itQuad->second.opcode == "J<=") {


		}
		if (itQuad->second.opcode == "J>") {


		}
		if (itQuad->second.opcode == "J>=") {


		}
		if (itQuad->second.opcode == "J==") {


		}
		if (itQuad->second.opcode == "J!=") {


		}
		if (itQuad->second.opcode == ":=") {


		}
	}








}


int main() {
	init_Reserve();//�����ֱ��ʼ��
	init_Boundary();//������ʼ��
	init_Operator();//��������ʼ��
	Symbol.clear();//��ʶ������ʼ��
	Digit.clear();//��������ʼ��
	index = 0;
	character = ' ';
	token = "";
	cout << "��������ʷ�������Դ������룺����#�����������\n" << endl;
	//Դ����������봦��
	while (cin >> in && in[in.size() - 1] != '#') {
		instr = instr + " " + in;
	}
	//ʶ���Ԫ���ʼ��
	Binary word(0, 0, "-");
	//ѭ�����дʷ�����ֱ��ʶ�����е��ʷ���
	while (index < instr.size()) {
		word = LexAnalyze();
		all[ip++] = word;
	}
	
	cout << "\n==================ƥ����==================\n" << endl;
	Analysis();

	//չʾ����ĸ��ִʻ��
	cout << "\n==================�ʻ��չʾ==================\n" << endl;
	show_table();

	cout << endl;
	cout << endl;


	cout << "\n==================�﷨��(ǰ�����)==================\n" << endl;
	traverse(root);

	cout << endl;
	cout << endl;
	cout << "\n==================��Ԫʽ��==================\n" << endl;
	for (itQuad = Quadruples.begin(); itQuad != Quadruples.end(); itQuad++) {
		cout << itQuad->first << "   " << itQuad->second << endl;
	}

	cout << endl;
	cout << endl;
	cout << "\n==================Ŀ����루δ��ɣ�==================\n" << endl;
	generateCode();
	for (itCode = Code.begin(); itCode != Code.end(); itCode++) {
		cout << itCode->first <<"\t"<< itCode->second << endl;

	}


	//cout << "------------������--------------" << endl;*/
	/*int n=10;
	cout<<to_string(n+1)<<endl;*///intתstring
	
	//vector
	//vector<string> str;
	//str.push_back("root");
	//str.push_back("doge");
	///*cout << str[0] << endl;
	//cout << str[1] << endl;*/
	//vector<string>::iterator itv;
	//for (itv = str.begin(); itv != str.end(); itv++) {
	//	cout << *itv << endl;
	//}
	return 0;
}