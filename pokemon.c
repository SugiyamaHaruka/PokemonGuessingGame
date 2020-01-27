//ポケモン推測ゲーム
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MaxTree 1000
#define MaxSentence 1000

struct node {
	char sentence[MaxSentence];//名前や特徴
	struct node* yes;//右の子(yes)
	struct node* no;//左の子(no)
};

struct node* Question(struct node* start, struct node* LastAccess);//節の時
struct node* MakeNode(char* sentence);//新しいノードを作る
void error(char* s);//エラーを表示する
void Ready();//ゲームを始めるかどうかを尋ねる
int CheckAnswer();//yesかno、それ以外かを判定する
bool AskAnimal(struct node* start);//葉の時
void BuildNode(struct node* start);//(推測できなかったとき)新しい要素を増やす
bool PlayAgain();//もう一度行うかどうかを尋ねる
struct node AnimalTree[MaxTree];//今回利用する木
//////////////////////////////////
//	　　						炎タイプ
//	　		yes.空を飛ぶ					no.地面タイプ
//yes.ファイアー　　no.ヒトカゲ		yes.フライゴン	no.ゼニガメ
/////////////////////////////////

int main(void) {
	printf("ポケモン推測ゲームにようこそ\n");
	bool PlayLoop = true;
	Ready();
	///////////////////////////////////////
	struct node* start = MakeNode("炎タイプ");
	start->yes = MakeNode("空を飛ぶ");
	start->no = MakeNode("地面タイプ");
	start->yes->yes = MakeNode("ファイアー");
	start->yes->no = MakeNode("ヒトカゲ");
	start->no->yes = MakeNode("フライゴン");
	start->no->no = MakeNode("ゼニガメ");
	///////////////////////////////////////////
	struct node* last = NULL;
	while (PlayLoop == true) {
		last = Question(start, last);//質問していく
		if (AskAnimal(last) == true) {//推測できた時
			printf("推測できました！\n");
		}
		else {//推測できなかったとき
			printf("推測できませんでした\n");
			BuildNode(last);
			printf("新しいデータを追加しました。次は推測して見せます！\n");
		}
		PlayLoop = PlayAgain();//もう一度遊ぶかどうかを尋ねる
	}
	printf("さようなら！");
	return 0;
}
int CheckAnswer() {//yesかno、それ以外かを判定する
	char* s[3];
	scanf("%s", &s);
	if (strcmp(s, "YES") == 0 || strcmp(s, "Yes") == 0 || strcmp(s, "yes") == 0) {//yes
		return 1;
	}
	else if (strcmp(s, "NO") == 0 || strcmp(s, "No") == 0 || strcmp(s, "no") == 0) {//no
		return 0;
	}
	else {//それ以外
		error("YesかNoで答えてください");
	}
}
struct node* MakeNode(char* sentence) {//新しいノードを作る
	struct node* p;
	if ((p = (struct node*)malloc(sizeof(struct  node))) == NULL)
		error("ノードを作ることができません\n");
	p->no = NULL;
	p->yes = NULL;
	strcpy(p->sentence, sentence);
	return p;
}
void error(char* s) {//エラーを表示する
	fprintf(stderr, s);
	exit(1);
}
struct node* Question(struct node* start, struct node* LastAccess) {//節の時。質問する
	int UserAnswer;
	LastAccess = start;
	if (start->yes == NULL && start->no == NULL) {//葉に来た時
		return LastAccess;
	}
	else {
		printf("「%s」---Yes/No??:", start->sentence);
		UserAnswer = CheckAnswer();
		if (UserAnswer == 0) {//No
			Question(start->no, LastAccess);
		}
		else {//Yes
			Question(start->yes, LastAccess);
		}
	}
}
void Ready() {//ゲームを始めるかどうかを尋ねる
	printf("ゲームをおこないますか?---Yes/No：");
	if (CheckAnswer() == 1) {//Yes
		printf("お楽しみください！\n");
	}
	else {//No
		printf("さようなら！\n");
		exit();
	}
}
bool AskAnimal(struct node* start) {//葉の時。ポケモンをたずねる
	int UserAnswer;
	printf("あなたの推測したポケモンは「%s」?---Yes/No:", start->sentence);
	UserAnswer = CheckAnswer();
	if (UserAnswer == 0) {//No
		return false;
	}
	else {//Yes
		return true;
	}
}
void BuildNode(struct node* start) {//(推測できなかったとき)新しい要素を増やす
	char AnimalName[MaxSentence];
	char feature[MaxSentence];
	printf("あなたの推測したかったポケモンの名前を教えてください。:");
	scanf("%s", &AnimalName);

	printf("そのポケモンの特徴を教えてください。:");
	scanf("%s", &feature);

	struct node* YesNode = MakeNode(AnimalName);
	struct node* NoNode = MakeNode(start->sentence);

	strcpy(start->sentence, feature);
	start->yes = YesNode;
	start->no = NoNode;
}
bool PlayAgain() {//もう一度行うかどうかを尋ねる
	int Answer;
	printf("もう一度遊びますか？---Yes/No：");
	Answer = CheckAnswer();
	if (Answer == 0) {//No
		return false;
	}
	else {//Yes
		return true;
	}
}