#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

void saveScore(int score, int oldscore)
{
    SD.begin(4); //FIXME Replace 4 with the appropriate pin
    if (SD.exists("Snake_Highscore.txt"))
    {
        SD.remove("Snake_Highscore.txt");
    }
    File scoreFile = SD.open("Snake_Highscore.txt");

    if (score >= oldscore)
    {
        scoreFile.println(score);
    }
    else 
    {
        scoreFile.println(oldscore);
    }

    scoreFile.close();
}

int highScore()
{
    SD.begin(4); // FIMXE Replace 4 with the approprate pin
    if (!SD.exists("Snake_Highscore.txt"))
    {
        return 0;
    }

    File scoreFile = SD.open("Snake_Highscore.txt");

    if (scoreFile.available())
    {
        int score = scoreFile.read();
        scoreFile.close();
        return score;
    }
    else
    {
        scoreFile.close();
        return 0;
    }
}