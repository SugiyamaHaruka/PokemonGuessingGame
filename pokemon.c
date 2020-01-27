//�|�P���������Q�[��
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MaxTree 1000
#define MaxSentence 1000

struct node {
	char sentence[MaxSentence];//���O�����
	struct node* yes;//�E�̎q(yes)
	struct node* no;//���̎q(no)
};

struct node* Question(struct node* start, struct node* LastAccess);//�߂̎�
struct node* MakeNode(char* sentence);//�V�����m�[�h�����
void error(char* s);//�G���[��\������
void Ready();//�Q�[�����n�߂邩�ǂ�����q�˂�
int CheckAnswer();//yes��no�A����ȊO���𔻒肷��
bool AskAnimal(struct node* start);//�t�̎�
void BuildNode(struct node* start);//(�����ł��Ȃ������Ƃ�)�V�����v�f�𑝂₷
bool PlayAgain();//������x�s�����ǂ�����q�˂�
struct node AnimalTree[MaxTree];//���񗘗p�����
//////////////////////////////////
//	�@�@						���^�C�v
//	�@		yes.�����					no.�n�ʃ^�C�v
//yes.�t�@�C�A�[�@�@no.�q�g�J�Q		yes.�t���C�S��	no.�[�j�K��
/////////////////////////////////

int main(void) {
	printf("�|�P���������Q�[���ɂ悤����\n");
	bool PlayLoop = true;
	Ready();
	///////////////////////////////////////
	struct node* start = MakeNode("���^�C�v");
	start->yes = MakeNode("�����");
	start->no = MakeNode("�n�ʃ^�C�v");
	start->yes->yes = MakeNode("�t�@�C�A�[");
	start->yes->no = MakeNode("�q�g�J�Q");
	start->no->yes = MakeNode("�t���C�S��");
	start->no->no = MakeNode("�[�j�K��");
	///////////////////////////////////////////
	struct node* last = NULL;
	while (PlayLoop == true) {
		last = Question(start, last);//���₵�Ă���
		if (AskAnimal(last) == true) {//�����ł�����
			printf("�����ł��܂����I\n");
		}
		else {//�����ł��Ȃ������Ƃ�
			printf("�����ł��܂���ł���\n");
			BuildNode(last);
			printf("�V�����f�[�^��ǉ����܂����B���͐������Č����܂��I\n");
		}
		PlayLoop = PlayAgain();//������x�V�Ԃ��ǂ�����q�˂�
	}
	printf("���悤�Ȃ�I");
	return 0;
}
int CheckAnswer() {//yes��no�A����ȊO���𔻒肷��
	char* s[3];
	scanf("%s", &s);
	if (strcmp(s, "YES") == 0 || strcmp(s, "Yes") == 0 || strcmp(s, "yes") == 0) {//yes
		return 1;
	}
	else if (strcmp(s, "NO") == 0 || strcmp(s, "No") == 0 || strcmp(s, "no") == 0) {//no
		return 0;
	}
	else {//����ȊO
		error("Yes��No�œ����Ă�������");
	}
}
struct node* MakeNode(char* sentence) {//�V�����m�[�h�����
	struct node* p;
	if ((p = (struct node*)malloc(sizeof(struct  node))) == NULL)
		error("�m�[�h����邱�Ƃ��ł��܂���\n");
	p->no = NULL;
	p->yes = NULL;
	strcpy(p->sentence, sentence);
	return p;
}
void error(char* s) {//�G���[��\������
	fprintf(stderr, s);
	exit(1);
}
struct node* Question(struct node* start, struct node* LastAccess) {//�߂̎��B���₷��
	int UserAnswer;
	LastAccess = start;
	if (start->yes == NULL && start->no == NULL) {//�t�ɗ�����
		return LastAccess;
	}
	else {
		printf("�u%s�v---Yes/No??:", start->sentence);
		UserAnswer = CheckAnswer();
		if (UserAnswer == 0) {//No
			Question(start->no, LastAccess);
		}
		else {//Yes
			Question(start->yes, LastAccess);
		}
	}
}
void Ready() {//�Q�[�����n�߂邩�ǂ�����q�˂�
	printf("�Q�[���������Ȃ��܂���?---Yes/No�F");
	if (CheckAnswer() == 1) {//Yes
		printf("���y���݂��������I\n");
	}
	else {//No
		printf("���悤�Ȃ�I\n");
		exit();
	}
}
bool AskAnimal(struct node* start) {//�t�̎��B�|�P�����������˂�
	int UserAnswer;
	printf("���Ȃ��̐��������|�P�����́u%s�v?---Yes/No:", start->sentence);
	UserAnswer = CheckAnswer();
	if (UserAnswer == 0) {//No
		return false;
	}
	else {//Yes
		return true;
	}
}
void BuildNode(struct node* start) {//(�����ł��Ȃ������Ƃ�)�V�����v�f�𑝂₷
	char AnimalName[MaxSentence];
	char feature[MaxSentence];
	printf("���Ȃ��̐��������������|�P�����̖��O�������Ă��������B:");
	scanf("%s", &AnimalName);

	printf("���̃|�P�����̓����������Ă��������B:");
	scanf("%s", &feature);

	struct node* YesNode = MakeNode(AnimalName);
	struct node* NoNode = MakeNode(start->sentence);

	strcpy(start->sentence, feature);
	start->yes = YesNode;
	start->no = NoNode;
}
bool PlayAgain() {//������x�s�����ǂ�����q�˂�
	int Answer;
	printf("������x�V�т܂����H---Yes/No�F");
	Answer = CheckAnswer();
	if (Answer == 0) {//No
		return false;
	}
	else {//Yes
		return true;
	}
}