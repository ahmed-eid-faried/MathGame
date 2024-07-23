#include <iostream>
#include <string>
using namespace std;
enum enQuestionType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mod = 5, MixType = 6, };
enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };
enum enWinOrNot { Win = 1, Not = 0 };
struct stResultRound {
	short	NumOFRound;
	int Num1;
	int Num2;
	float CorrectAnswer;
	float	PlayerAnswer;
	enQuestionType QuestionType;
	enQuestionLevel QuestionLevel;
	enWinOrNot Winner;
};
struct stGameResult {
	short	NumOFRoundsGame;
	short	ScorePlayer;
	enQuestionType QuestionType;
	enQuestionLevel QuestionLevel;
	enWinOrNot Winner;
};
float  ReadNumber(string Message) {
	float Num;
	cout << Message;
	cin >> Num;
	return  Num;
}
int  ReadPositiveNumber(string Message) {
	int Num;
	do {
		cout << Message;
		cin >> Num;
	} while (Num < 0);
	return  Num;
}
int ReadNumberInRange(int From, int To, string Message = "ENTER NUMBER") {
	int NUM;
	do {
		cout << Message << " FROM " << to_string(From) << " TO " << to_string(To) << ": ";
		cin >> NUM;
	} while (NUM < From || NUM > To);
	return NUM;
}
int RandomNumber(int From, int To) {
	return (rand() % (To - From + 1)) + From;
}
void CheckWinnerGame(stGameResult& GameResult) {
	if (GameResult.ScorePlayer >= (float)GameResult.NumOFRoundsGame / 2) {
		GameResult.Winner = enWinOrNot::Win;
		cout << "--------------------------------------------------------------" << endl;
		cout << "\tFinal Results Is Pass :-)" << endl;
		cout << "--------------------------------------------------------------" << endl;
	}
	else {
		GameResult.Winner = enWinOrNot::Not;
		cout << "--------------------------------------------------------------" << endl;
		cout << "\tFinal Results Is Fail :-(" << endl;
		cout << "--------------------------------------------------------------" << endl;
	}
}
enWinOrNot CheckWinnerRound(stResultRound ResultRound) {
	return (enWinOrNot)(ResultRound.CorrectAnswer == ResultRound.PlayerAnswer);
}
void ChangeScreen(enWinOrNot Winner) {
	switch (Winner)
	{
	case enWinOrNot::Not:
		cout << '\a';
		system("color 4F");
		break;
	case enWinOrNot::Win:
		system("color 2F");
		break;
	default:
		break;
	}
}
int GetQuestionLevel(enQuestionLevel QuestionLevel) {
	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
		return RandomNumber(1, 10);
	case enQuestionLevel::Med:
		return RandomNumber(1, 200);
	case enQuestionLevel::Hard:
		return RandomNumber(1, 10000000);
	default:
		return RandomNumber(1, 50);
	}
}
float AnswerQuestion(stResultRound& ResultRound) {
	switch (ResultRound.QuestionType)
	{
	case enQuestionType::Add:
		return ResultRound.Num1 + ResultRound.Num2;
	case enQuestionType::Sub:
		return ResultRound.Num1 - ResultRound.Num2;
	case enQuestionType::Mul:
		return ResultRound.Num1 * ResultRound.Num2;
	case enQuestionType::Div:
		return ResultRound.Num1 / ResultRound.Num2;
	case enQuestionType::Mod:
		return ResultRound.Num1 % ResultRound.Num2;
		//case enQuestionType::Mix:
		//	return Num1 + ResultRound.Num2;
	default:
		return ResultRound.Num1 + ResultRound.Num2;
	}

}
char GetQuestionTypeCode(enQuestionType QuestionType) {
	switch (QuestionType)
	{
	case Add:
		return '+';
	case Sub:
		return '-';
	case Mul:
		return '*';
	case Div:
		return '/';
	case Mod:
		return '%';
		//case Mix:
		//	return '+';
	default:
		return '+';
	}
}
string GetQuestionTypeName(enQuestionType QuestionType) {
	switch (QuestionType)
	{
	case Add:
		return "Add";
	case Sub:
		return "Sub";
	case Mul:
		return "Mul";
	case Div:
		return "Div";
	case Mod:
		return "Mod";
	case MixType:
		return "Mix";
	default:
		return "Add";
	}
}
string GetQuestionLevelName(enQuestionLevel QuestionLevel) {
	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
		return "Easy";
	case enQuestionLevel::Med:
		return "Med";
	case enQuestionLevel::Hard:
		return "Hard";
	case enQuestionLevel::MixLevel:
		return "MixLevel";
	default:
		return "Easy";
	}
}
enQuestionType GetMixQuestionType(enQuestionType QuestionType) {
	if (QuestionType == enQuestionType::MixType) {
		return (enQuestionType)RandomNumber(1, 5);
	}
	else {
		return  QuestionType;
	}
}
enQuestionLevel GetMixQuestionLevel(enQuestionLevel QuestionLevel) {
	if (QuestionLevel == enQuestionLevel::MixLevel) {
		return (enQuestionLevel)RandomNumber(1, 3);
	}
	else {
		return  QuestionLevel;
	}
}
void PrintQuestion(short NumOFRoundsGame, short CurrentRound, stResultRound  ResultRound) {
	cout << "\n\nQuestion [" << CurrentRound << '/' << NumOFRoundsGame << "]:" << endl;
	cout << ResultRound.Num1 << endl;
	cout << ResultRound.Num2 << "  " << GetQuestionTypeCode(ResultRound.QuestionType) << endl;
	cout << "--------------------------------------------------------------" << endl;
}
void ShowResultRound(stResultRound& ResultRound) {
	ChangeScreen(ResultRound.Winner);
	if (ResultRound.Winner == enWinOrNot::Win) {
		cout << "Right Answer :-)" << endl;
	}
	else {
		cout << "Wrong Answer :-(" << endl;
		cout << "The Right Answer Is: " << ResultRound.CorrectAnswer << endl;
	}

}
void ShowResultGame(stGameResult& GameResult) {
	cout << endl << endl << endl;
	CheckWinnerGame(GameResult);
	ChangeScreen(GameResult.Winner);
	cout << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "---------------------- [ GAME RESULTS ] ----------------------" << endl;
	cout << "Number Of Questions: \t" << GameResult.NumOFRoundsGame << endl;
	cout << "Question Level: \t" << GetQuestionLevelName(GameResult.QuestionLevel) << endl;
	cout << "Question Type: \t" << GetQuestionTypeName(GameResult.QuestionType) << endl;
	cout << "Right Answers: \t" << GameResult.ScorePlayer << endl;
	cout << "Wrong Answers: \t" << GameResult.NumOFRoundsGame - GameResult.ScorePlayer << endl;
	cout << "--------------------------------------------------------------" << endl;
}
void PlayGame(short NumOFRoundsGame, enQuestionLevel QuestionLevel, enQuestionType QuestionType) {
	stResultRound ResultRound;
	stGameResult GameResult;
	GameResult.ScorePlayer = 0;
	GameResult.NumOFRoundsGame = NumOFRoundsGame;
	GameResult.QuestionLevel = QuestionLevel;
	GameResult.QuestionType = QuestionType;
	ResultRound.NumOFRound = NumOFRoundsGame;
	for (int i = 1; i <= NumOFRoundsGame; i++)
	{
		ResultRound.Num1 = GetQuestionLevel(QuestionLevel);
		ResultRound.Num2 = GetQuestionLevel(QuestionLevel);
		ResultRound.QuestionType = GetMixQuestionType(QuestionType);
		ResultRound.QuestionLevel = GetMixQuestionLevel(QuestionLevel);
		ResultRound.CorrectAnswer = AnswerQuestion(ResultRound);
		///////////////////////////////////////////////////////////
		PrintQuestion(NumOFRoundsGame, i, ResultRound);
		ResultRound.PlayerAnswer = ReadNumber("");
		cout << endl;
		///////////////////////////////////////////////////////////
		ResultRound.Winner = CheckWinnerRound(ResultRound);
		//ResultRound.NumOFRound = i;
		if (ResultRound.Winner == enWinOrNot::Win) {
			GameResult.ScorePlayer++;
		}
		///////////////////////////////////////////////////////////
		ShowResultRound(ResultRound);
	}
	ShowResultGame(GameResult);
}
void ResetScreen() {
	system("cls");
	system("color 0F");

}
void SartGame() {
	int IsFinish = 1;
	while (IsFinish) {
		ResetScreen();
		short NumOFQuestionGame = ReadPositiveNumber("How many questions do you to answer: ");
		enQuestionLevel QuestionLevel = (enQuestionLevel)ReadNumberInRange(1, 4, "Enter Question Level: [1] Easy, [2] Med, [3] Hard, [4] Mix : ");
		enQuestionType QuestionType = (enQuestionType)ReadNumberInRange(1, 6, "Enter Question Type: [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mod, [6] Mix : ");
		PlayGame(NumOFQuestionGame, QuestionLevel, QuestionType);
		cout << endl << endl;
		cout << "DO YOU WANT TO PLAY AGAIN? [0]:No,[1]Yes? ";
		cin >> IsFinish;
		if (IsFinish != 1)break;
	}

}
int main()
{
	srand((unsigned)time(NULL));
	SartGame();
}