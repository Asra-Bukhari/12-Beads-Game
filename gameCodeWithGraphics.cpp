#include <iostream>
#include <cstring>
#include <fstream>
#include <thread>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

void Display(RenderWindow&);
int cointoss(RenderWindow&, const string&, const string&);
void drawLines(RenderWindow&);
void drawBeads(CircleShape, RenderWindow&);
void game(RenderWindow&, const string&, const string&);
void winner(RenderWindow&, Color, string, string);
void saveGameState(const string& fileName, CircleShape beads[5][5], const string& p1, const string& p2, Color d1, Color d2, int turn, int p1beads, int p2beads);
void loadGameState(const string& fileName, CircleShape beads[5][5], string& p1, string& p2, Color& d1, Color& d2, int& turn, int& p1beads, int& p2beads);
const int beadRadius = 12;
const int boardRadius = 150;
int turn = 3;
string p1, p2;
Color d1, d2;

Font font;
Text title("12 Beads Game", font, 50);


CircleShape beads[5][5];

string playerName1;
string playerName2;

int red = 12, green = 12;
void LoadingBar() {
    // Create a window
    RenderWindow window(VideoMode(800, 600), "12 Beads Game");
    window.setFramerateLimit(60);
    Texture texture;
    if (!texture.loadFromFile("./formenu.jpg"))
    {
        cout << "Load failed" << endl;
        system("pause");
    }

    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(50, 10);

    //Set the initial loading bar position and size
    RectangleShape loadingBar(Vector2f(0, 10));
    loadingBar.setFillColor(Color::White);
    loadingBar.setPosition(250, 300);

    //Set up the font and text for the loading message
    Font font;
    if (!font.loadFromFile("BodoniFLF-Bold.ttf")) {
        std::cerr << "Font not found!\n";
        return;
    }

    Text loadingText("Loading...", font, 30);
    loadingText.setPosition(350, 250);
    loadingText.setFillColor(Color::White);
    //Draw the initial window
    window.clear(Color::Black);
    window.draw(loadingBar);
    window.draw(loadingText);
    window.display();

    //Simulate loading progress for at least 5 seconds
    auto startTime = chrono::steady_clock::now();
    while (true) {
        //Get the elapsed time
        auto currentTime = chrono::steady_clock::now();
        auto elapsedTime = chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

        if (elapsedTime >= 5) {
            break;  // Exit the loop after 5 seconds
        }

        // Adjust the loading bar size based on progress
        loadingBar.setSize(Vector2f(80 * (elapsedTime % 6), 50));

        // Redraw the window
        window.clear(Color::Black);
        window.draw(sprite);
        window.draw(loadingBar);
        window.draw(loadingText);
        window.display();
        // Simulate work being done by sleeping for a short duration
        this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    // Keep the window open for a moment before closing
    this_thread::sleep_for(std::chrono::seconds(1));
}
void highlight(sf::RenderWindow& window, Text optionsText, RectangleShape box)
{
    box.setOutlineThickness(5);
    box.setFillColor(Color::Yellow);
    window.draw(box);
    window.draw(optionsText);
    window.display();
    // Introduce a delay of 2 seconds
    std::this_thread::sleep_for(std::chrono::seconds(1));

}

void initializeBeads(CircleShape beads[][5], RenderWindow& window)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (i < 2)      // Red
            {

                beads[i][j].setRadius(beadRadius);
                beads[i][j].setFillColor(Color::Red);
                beads[i][j].setPosition(189 + j * 100, 133 + i * 100);
                beads[i][j].setOrigin(beadRadius, beadRadius);

            }
            else if (i == 2)
            {

                if (j < 2)
                {
                    beads[i][j].setRadius(beadRadius);
                    beads[i][j].setFillColor(Color::Red);
                    beads[i][j].setPosition(189 + j * 100, 133 + i * 100);
                    beads[i][j].setOrigin(beadRadius, beadRadius);
                }
                else if (j == 2)
                {
                    beads[i][j].setRadius(beadRadius);
                    beads[i][j].setFillColor(Color::Transparent);
                    beads[i][j].setPosition(189 + j * 100, 133 + i * 100);
                    beads[i][j].setOrigin(beadRadius, beadRadius);
                }
                else
                {
                    beads[i][j].setRadius(beadRadius);
                    beads[i][j].setFillColor(Color::Green);
                    beads[i][j].setPosition(189 + j * 100, 133 + i * 100);
                    beads[i][j].setOrigin(beadRadius, beadRadius);
                }

            }
            else
            {

                beads[i][j].setRadius(beadRadius);
                beads[i][j].setFillColor(Color::Green);
                beads[i][j].setPosition(189 + j * 100, 133 + i * 100);
                beads[i][j].setOrigin(beadRadius, beadRadius);

            }

        }
    }

}

void drawLines(RenderWindow& window)
{

    //Rectangular Grid of 16 boxes
    RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(400, 400));
    rectangle.setPosition(190, 130);

    //Set the fill color to transparent
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineColor(Color::Black);
    rectangle.setOutlineThickness(3);

    //Diamond on the Grid
    ConvexShape diamond;
    // Set the number of points (vertices) in the diamond
    diamond.setPointCount(4);

    //Set the position of each vertex to form a diamond
    diamond.setPointCount(4);
    diamond.setPoint(0, Vector2f(190 + 200, 130));    // Top
    diamond.setPoint(1, Vector2f(590, 330));          // Right
    diamond.setPoint(2, Vector2f(390, 530));          // Bottom
    diamond.setPoint(3, Vector2f(190, 330));           // Left 

    // Set the fill color
    diamond.setFillColor(Color::Transparent);
    diamond.setOutlineColor(Color::Black);
    diamond.setOutlineThickness(3);

    VertexArray diagonals(Lines, 4);
    diagonals[0].position = Vector2f(190, 130);        // Top-left corner
    diagonals[1].position = Vector2f(590, 530);       // Bottom-right corner
    diagonals[2].position = Vector2f(190, 530);       // Bottom-left corner
    diagonals[3].position = Vector2f(590, 130);        // Top-right corner
    for (int i = 0; i < 4; ++i) {
        diagonals[i].color = sf::Color::Black;
    }
    VertexArray horizontalLines(Lines, 2);
    for (int i = 0; i < 2; ++i) {
        float y = 130 + (i + 1) * 100; // Adjust this value based on the desired spacing
        horizontalLines[i].position = Vector2f(190, y);
        horizontalLines[i].color = Color::Black;
    }

    // Vertical lines (within each part)
    sf::VertexArray verticalLines(sf::Lines, 6);
    for (int i = 0; i < 3; ++i) {
        float x = 190 + (i + 1) * 100; // Adjust this value based on the desired spacing
        verticalLines[i * 2].position = sf::Vector2f(x, 130);
        verticalLines[i * 2 + 1].position = sf::Vector2f(x, 530);
        for (int j = 0; j < 2; ++j) {
            verticalLines[i * 2 + j].color = sf::Color::Black;
        }
    }
    VertexArray horizontalSmallLines(Lines, 6);
    for (int i = 0; i < 5; ++i) {
        float y = 130 + (i + 1) * 100; // Adjust this value based on the desired spacing
        // Ensure that the calculated indices are within bounds
        int index1 = i * 2;
        int index2 = i * 2 + 1;

        // Check if the indices are within bounds before accessing the array
        if (index1 < horizontalSmallLines.getVertexCount() && index2 < horizontalSmallLines.getVertexCount()) {
            horizontalSmallLines[index1].position = sf::Vector2f(190, y);
            horizontalSmallLines[index2].position = sf::Vector2f(590, y);
            for (int j = 0; j < 2; ++j) {
                // Set other properties if needed
                horizontalSmallLines[index1 + j].color = sf::Color::Black;
            }
        }
    }

    window.draw(rectangle);
    window.draw(diamond);
    window.draw(diagonals);

    window.draw(horizontalLines);
    window.draw(verticalLines);

    window.draw(horizontalSmallLines);
}

void drawBeads(CircleShape beads[][5], RenderWindow& window)
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; j++)
        {
            window.draw(beads[j][i]);
        }
    }
}

void Instruction_Menu(RenderWindow& window)
{
    Texture texture;
    if (!texture.loadFromFile("./formenu.jpg"))
    {
        cout << "Load failed" << endl;
        system("pause");
    }

    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(50, 10);

    Text Instruction("Instructions:", font, 40);
    Instruction.setPosition(150, 200);
    Instruction.setFillColor(Color::White);
    Instruction.setOutlineThickness(3);
    Instruction.setOutlineColor(Color::Black);

    Font font2;
    font2.loadFromFile("BodoniFLF-Bold.ttf");
    Text Option("1. Each Player Has 12 Beads \n2. Players Take Turns \n3. You Can Only Move on Path Given\n4. Capture Enemies All Beads To Win", font2, 30);
    Option.setPosition(150, 270);
    Option.setFillColor(Color::Black);

    RectangleShape box1(Vector2f(150, 40));
    box1.setFillColor(Color::Green);
    box1.setPosition(320, 450);
    box1.setOutlineColor(Color::Black);
    Text ret_menu("Back", font, 30);
    ret_menu.setPosition(360, 450);
    ret_menu.setFillColor(Color::Black);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::Closed)
            {
                window.close();
            }


            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePosition = Mouse::getPosition(window);

                if (box1.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                {
                    highlight(window, ret_menu,box1);
                    return;
                }
            }
        }
        window.clear(Color::Black);
        window.draw(sprite);
        window.draw(title);
        window.draw(Instruction);
        window.draw(Option);
        window.draw(box1);
        window.draw(ret_menu);


        window.display();
    }

}

int cointoss(RenderWindow& window, const string& playerName1, const string& playerName2)
{
    Texture texture;
    if (!texture.loadFromFile("./formenu.jpg"))
    {
        cout << "Load failed" << endl;
        system("pause");
    }

    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(50, 10);
    Text CoinToss("Player1 Choose Heads or Tails", font, 40);
    CoinToss.setPosition(150, 200.f);
    CoinToss.setFillColor(Color::Black);
    Text Option("\t\t Heads \t \t Tails", font, 30);
    Option.setPosition(150, 270.f);
    Option.setFillColor(Color::Black);
    RectangleShape box1(Vector2f(130, 40));
    box1.setFillColor(Color::White);
    box1.setPosition(220, 270);
    box1.setOutlineColor(Color::Black);

    RectangleShape box2(Vector2f(130, 40));
    box2.setFillColor(Color::White);
    box2.setPosition(400, 270);
    box2.setOutlineColor(Color::Black);
    Text Start_Game("Click To Play !", font, 40);
    Start_Game.setPosition(180, 450);
    Start_Game.setFillColor(Color::Black);
    int toss = -1; // Initialize toss to an invalid value

    srand(time(0));
    int coin = -1;
    coin = rand() % 2;

    bool check = false;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePosition = Mouse::getPosition(window);

                //  Check if any menu option is clicked
                if (box1.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                {
                    if (!check) {
                        highlight(window, Option, box1);
                        toss = 0; // Heads
                        check = true;
                    }  
                }
                else if (box2.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                {
                    if (!check) {
                        highlight(window, Option, box2);
                        toss = 1; // Tails
                        check = true;
                    }
                }
               
                else if (Start_Game.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                {
                    cout << "Starting Game ... ";

                    if (toss == coin)
                    {
                        game(window, playerName1, playerName2);
                    }
                    else
                    {
                        game(window, playerName2, playerName1);
                    }
                    window.close();
                }
               
            }
        }

        window.clear(Color::Black);
        window.draw(sprite);
        window.draw(box1);
        window.draw(box2);
        window.draw(title);
        window.draw(CoinToss);
        window.draw(Option);

        Text res;
        res.setFont(font);
        res.setCharacterSize(40);
        res.setPosition(150, 340);

        if (coin == 0)
        {
            res.setString("It's Heads!");
        }
        else
        {
            res.setString("It's Tails!");
        }

        if (check)
        {
            Text resultText;
            resultText.setFont(font);
            resultText.setCharacterSize(40);
            resultText.setPosition(150, 390);

            if (toss == 0)
            {
                resultText.setString(playerName1 + " chose Heads!");
                window.draw(resultText);
                window.draw(res);
            }
            else if (toss == 1)
            {
                resultText.setString(playerName1 + " chose Tails!");
                window.draw(resultText);
                window.draw(res);
            }

            window.draw(Start_Game);
        }

        window.display();
    }

    if (toss == coin)
    {
        return 1;       // player one won the toss
    }
    else
    {
        return 0;       // player one lost the toss
    }
}

string getPlayerName(RenderWindow& window)
{
    Texture texture;
    if (!texture.loadFromFile("./formenu.jpg"))
    {
        cout << "Load failed" << endl;
        system("pause");
    }

    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(50, 10);
    string playerName = "";

    Text enterNameText("Enter Players Name:", font, 30);
    enterNameText.setPosition(150, 230);
    enterNameText.setFillColor(Color::White);
    enterNameText.setOutlineThickness(3);
    enterNameText.setOutlineColor(Color::Black);
    Text playerNameText("", font, 30);
    playerNameText.setPosition(150, 300);
    playerNameText.setFillColor(Color::White);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode > 66 && event.text.unicode < 128)        // Takes input in ascii and check if ascii greater than numbers and less than special characters
                {
                    playerName += event.text.unicode;
                    playerNameText.setString(playerName);
                }
            }

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Enter && !playerName.empty())
                {
                    return playerName;
                }
            }
        }

        window.clear(Color::Black);


        //  Draw elements for coin toss
        window.draw(sprite);
        window.draw(title);

        //  Draw elements for entering player name
        window.draw(enterNameText);
        window.draw(playerNameText);

        window.display();
    }

    return ""; // Return empty string if the window is closed before entering a name
}

void getPlayerPos(RenderWindow& window, const string& playerName1, const string& playerName2, int arr[])
{
    Texture texture;
    if (!texture.loadFromFile("./formenu.jpg"))
    {
        cout << "Load failed" << endl;
        system("pause");
    }

    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(50, 10);
    Text p1(playerName1 + " - " + to_string(red), font, 30);

    Text p2(playerName2 + " - " + to_string(green), font, 30);

    p1.setFillColor(Color::Red);
    p1.setPosition(200, 70);
    p1.setOutlineThickness(3);
    p1.setOutlineColor(Color::Black);
    p2.setFillColor(Color::Green);
    p2.setPosition(450, 70);
    p2.setOutlineThickness(3);
    p2.setOutlineColor(Color::Black);
    string BeadPosition;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                saveGameState("Save_State.txt", beads, playerName1, playerName2, d1, d2, turn, red, green);
                window.close();
                break;
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePosition = Mouse::getPosition(window);    // Mouse Position

                // Check if any bead is clicked
                for (int i = 0; i < 5; ++i)
                {
                    for (int j = 0; j < 5; ++j)
                    {
                        if (beads[i][j].getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                        {
                            arr[0] = i;
                            arr[1] = j;
                            return;

                        }
                    }
                }
            }

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Enter && !BeadPosition.empty())
                {

                }
            }
        }

        window.clear(Color::Black);
        window.draw(sprite);
        drawLines(window);
        drawBeads(beads, window);

        // Draw elements for coin toss

        window.draw(p1);
        window.draw(p2);

        window.display();
    }

}

void Display(RenderWindow& window)
{
    Texture texture;
    if (!texture.loadFromFile("./formenu.jpg"))
    {
        cout << "Load failed" << endl;
        system("pause");
    }

    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(50, 10);
    font.loadFromFile("Light Bearer.ttf");
    title.setCharacterSize(70);
    title.setPosition(180, 100);
    title.setFillColor(Color::Yellow);
    title.setOutlineColor(Color::Black);
    title.setOutlineThickness(3);

    Text startText(" New Game", font, 30);
    startText.setPosition(300, 250.f);
    startText.setFillColor(Color::Black);
    Text resumeText(" Resume", font, 30);
    resumeText.setPosition(300, 310.f);
    resumeText.setFillColor(Color::Black);
    Text instructionsText(" Instructions", font, 30);
    instructionsText.setPosition(300, 380.f);
    instructionsText.setFillColor(Color::Black);
    Text exitText(" Exit", font, 30);
    exitText.setPosition(300, 450.f);
    exitText.setFillColor(Color::Black);

    RectangleShape box1(Vector2f(250, 40)), box2(Vector2f(250, 40)), box3(Vector2f(250, 40)), box4(Vector2f(250, 40));
    box1.setFillColor(Color::White);
    box1.setPosition(250, 250);
    box1.setOutlineColor(Color::Black);
    box2.setFillColor(Color::Green);
    box2.setPosition(250, 310);
    box2.setOutlineColor(Color::Black);
    box3.setFillColor(Color::White);
    box3.setPosition(250, 380);
    box3.setOutlineColor(Color::Black);
    box4.setFillColor(Color::White);
    box4.setPosition(250, 450);
    box4.setOutlineColor(Color::Black);

    initializeBeads(beads, window);


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
                break;
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                //  Get mouse position in pixel coordinates
                Vector2i mousePosition = Mouse::getPosition(window);

                //  Check if any menu option is clicked
                if (box1.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                {
                    highlight(window, startText, box1);

                    // Get Players Names
                    string playerName1 = getPlayerName(window);
                    string playerName2 = getPlayerName(window);

                    //  Move Text Outside Board
                    startText.setPosition(900, 900);
                    instructionsText.setPosition(900, 900);
                    exitText.setPosition(900, 900);

                    cout << "Hello " << playerName1 << endl;
                    cout << "Hello " << playerName2 << endl;

                    // Get Toss Value (1 = Player one Won Toss & 0 means Player one Lost Toss)
                    int choice = cointoss(window, playerName1, playerName2);

                    window.close();
                }
                if (box2.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                {
                    highlight(window, resumeText, box2);
                    loadGameState("Save_State.txt", beads, playerName1, playerName2, d1, d2, turn, red, green);
                    game(window, playerName1, playerName2);
                }
                else if (box3.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                {
                    highlight(window, instructionsText, box3);
                    Instruction_Menu(window);
                }
                else if (box4.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                {
                    highlight(window, exitText, box4);
                    window.close();
                }
            }
        }

        window.clear(Color::Black);


        // Draw the menu text on top of the background
        window.draw(sprite);
        window.draw(box1);
        window.draw(box2);
        window.draw(box3);
        window.draw(box4);
        window.draw(title);
        window.draw(startText);
        window.draw(instructionsText);
        window.draw(resumeText);
        window.draw(exitText);

        window.display();
    }
}

bool bead_Check()
{
    if (red < 1 || green < 1)
        return true;
    else
        return false;
}

bool implementation(int old_arr[], int new_arr[], Color  d1, Color d2, int& check, int& bead)
{//main logic(conditions)

    if (old_arr[0] == 0 && old_arr[1] == 0)
    {
        if (new_arr[0] == 0 && new_arr[1] == 1 && beads[0][1].getFillColor() == Color::Transparent)
            beads[0][1].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 1 && beads[1][1].getFillColor() == Color::Transparent)
            beads[1][1].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 0 && beads[1][0].getFillColor() == Color::Transparent)
            beads[1][0].setFillColor(d1);
        else if (new_arr[0] == 0 && new_arr[1] == 2 && beads[0][1].getFillColor() == d2 && beads[0][2].getFillColor() == Color::Transparent)
        {
            beads[0][2].setFillColor(d1);
            beads[0][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 2 && beads[1][1].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent)
        {
            beads[2][2].setFillColor(d1);
            beads[1][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 0 && beads[1][0].getFillColor() == d2 && beads[2][0].getFillColor() == Color::Transparent)
        {
            beads[2][0].setFillColor(d1);
            beads[1][0].setFillColor(d2);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[0][0].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 0 && old_arr[1] == 1)
    {
        if (new_arr[0] == 0 && new_arr[1] == 0 && beads[0][0].getFillColor() == Color::Transparent)
            beads[0][0].setFillColor(d1);
        else if (new_arr[0] == 0 && new_arr[1] == 2 && beads[0][2].getFillColor() == Color::Transparent)
            beads[0][2].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 1 && beads[1][1].getFillColor() == Color::Transparent)
            beads[1][1].setFillColor(d1);
        else if (new_arr[0] == 0 && new_arr[1] == 3 && beads[0][2].getFillColor() == d2 && beads[0][3].getFillColor() == Color::Transparent)
        {
            beads[0][3].setFillColor(d1);
            beads[0][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 1 && beads[1][1].getFillColor() == d2 && beads[2][1].getFillColor() == Color::Transparent)
        {
            beads[2][1].setFillColor(d1);
            beads[1][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[0][1].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 0 && old_arr[1] == 2)
    {
        if (new_arr[0] == 0 && new_arr[1] == 1 && beads[0][1].getFillColor() == Color::Transparent)
            beads[0][1].setFillColor(d1);
        else if (new_arr[0] == 0 && new_arr[1] == 3 && beads[0][3].getFillColor() == Color::Transparent)
            beads[0][3].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 1 && beads[1][1].getFillColor() == Color::Transparent)
            beads[1][1].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 2 && beads[1][2].getFillColor() == Color::Transparent)
            beads[1][2].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 3 && beads[1][3].getFillColor() == Color::Transparent)
            beads[1][3].setFillColor(d1);
        else if (new_arr[0] == 0 && new_arr[1] == 0 && beads[0][1].getFillColor() == d2 && beads[0][0].getFillColor() == Color::Transparent)
        {
            beads[0][0].setFillColor(d1);
            beads[0][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 0 && new_arr[1] == 4 && beads[0][3].getFillColor() == d2 && beads[0][4].getFillColor() == Color::Transparent)
        {
            beads[0][4].setFillColor(d1);
            beads[0][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 0 && beads[1][1].getFillColor() == d2 && beads[2][0].getFillColor() == Color::Transparent)
        {
            beads[2][0].setFillColor(d1);
            beads[1][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 2 && beads[1][2].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent)
        {
            beads[2][2].setFillColor(d1);
            beads[1][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 4 && beads[1][3].getFillColor() == d2 && beads[2][4].getFillColor() == Color::Transparent)
        {
            beads[2][4].setFillColor(d1);
            beads[1][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[0][2].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 0 && old_arr[1] == 3)
    {
        if (new_arr[0] == 0 && new_arr[1] == 2 && beads[0][2].getFillColor() == Color::Transparent)
            beads[0][2].setFillColor(d1);
        else if (new_arr[0] == 0 && new_arr[1] == 4 && beads[0][4].getFillColor() == Color::Transparent)
            beads[0][4].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 3 && beads[1][3].getFillColor() == Color::Transparent)
            beads[1][3].setFillColor(d1);
        else if (new_arr[0] == 0 && new_arr[1] == 1 && beads[0][2].getFillColor() == d2 && beads[0][1].getFillColor() == Color::Transparent)
        {
            beads[0][1].setFillColor(d1);
            beads[0][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 3 && beads[1][3].getFillColor() == d2 && beads[2][3].getFillColor() == Color::Transparent)
        {
            beads[2][3].setFillColor(d1);
            beads[1][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[0][3].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 0 && old_arr[1] == 4)
    {
        if (new_arr[0] == 0 && new_arr[1] == 3 && beads[0][3].getFillColor() == Color::Transparent)
            beads[0][3].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 3 && beads[1][3].getFillColor() == Color::Transparent)
            beads[1][3].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 4 && beads[1][4].getFillColor() == Color::Transparent)
            beads[1][4].setFillColor(d1);
        else if (new_arr[0] == 0 && new_arr[1] == 2 && beads[0][3].getFillColor() == d2 && beads[0][2].getFillColor() == Color::Transparent)
        {
            beads[0][2].setFillColor(d1);
            beads[0][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 2 && beads[1][3].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent)
        {
            beads[2][2].setFillColor(d1);
            beads[1][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 4 && beads[1][4].getFillColor() == d2 && beads[2][4].getFillColor() == Color::Transparent)
        {
            beads[2][4].setFillColor(d1);
            beads[1][4].setFillColor(d2);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[0][4].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 1 && old_arr[1] == 0)
    {
        if (new_arr[0] == 0 && new_arr[1] == 0 && beads[0][0].getFillColor() == Color::Transparent)
            beads[0][0].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 0 && beads[2][0].getFillColor() == Color::Transparent)
            beads[2][0].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 1 && beads[1][1].getFillColor() == Color::Transparent)
            beads[1][1].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 2 && beads[1][1].getFillColor() == d2 && beads[1][2].getFillColor() == Color::Transparent)
        {
            beads[1][2].setFillColor(d1);
            beads[1][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 3 && new_arr[1] == 0 && beads[2][0].getFillColor() == d2 && beads[3][0].getFillColor() == Color::Transparent)
        {
            beads[3][0].setFillColor(d1);
            beads[2][0].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[1][0].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 1 && old_arr[1] == 1)
    {
        if (new_arr[0] == 0 && new_arr[1] == 0 && beads[0][0].getFillColor() == Color::Transparent)
            beads[0][0].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 0 && beads[1][0].getFillColor() == Color::Transparent)
            beads[1][0].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 0 && beads[2][0].getFillColor() == Color::Transparent)
            beads[2][0].setFillColor(d1);
        else if (new_arr[0] == 0 && new_arr[1] == 1 && beads[0][1].getFillColor() == Color::Transparent)
            beads[0][1].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 1 && beads[2][1].getFillColor() == Color::Transparent)
            beads[2][1].setFillColor(d1);
        else if (new_arr[0] == 0 && new_arr[1] == 2 && beads[0][2].getFillColor() == Color::Transparent)
            beads[0][2].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 2 && beads[1][2].getFillColor() == Color::Transparent)
            beads[1][2].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 2 && beads[2][2].getFillColor() == Color::Transparent)
            beads[2][2].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 3 && beads[1][2].getFillColor() == d2 && beads[1][3].getFillColor() == Color::Transparent)
        {
            beads[1][3].setFillColor(d1);
            beads[1][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 3 && new_arr[1] == 1 && beads[2][1].getFillColor() == d2 && beads[3][1].getFillColor() == Color::Transparent)
        {
            beads[3][1].setFillColor(d1);
            beads[2][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 3 && new_arr[1] == 3 && beads[2][2].getFillColor() == d2 && beads[3][3].getFillColor() == Color::Transparent)
        {
            beads[3][3].setFillColor(d1);
            beads[2][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[1][1].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 1 && old_arr[1] == 2)
    {
        if (new_arr[0] == 0 && new_arr[1] == 2 && beads[0][2].getFillColor() == Color::Transparent)
            beads[0][2].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 1 && beads[1][1].getFillColor() == Color::Transparent)
            beads[1][1].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 2 && beads[2][2].getFillColor() == Color::Transparent)
            beads[2][2].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 3 && beads[1][3].getFillColor() == Color::Transparent)
            beads[1][3].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 0 && beads[1][1].getFillColor() == d2 && beads[1][0].getFillColor() == Color::Transparent)
        {
            beads[1][0].setFillColor(d1);
            beads[1][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 3 && new_arr[1] == 2 && beads[2][2].getFillColor() == d2 && beads[3][2].getFillColor() == Color::Transparent)
        {
            beads[3][2].setFillColor(d1);
            beads[2][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 1 && new_arr[1] == 4 && beads[1][3].getFillColor() == d2 && beads[1][4].getFillColor() == Color::Transparent)
        {
            beads[1][4].setFillColor(d1);
            beads[1][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[1][2].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 1 && old_arr[1] == 3)
    {
        if (new_arr[0] == 0 && new_arr[1] == 4 && beads[0][4].getFillColor() == Color::Transparent)
            beads[0][4].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 4 && beads[1][4].getFillColor() == Color::Transparent)
            beads[1][4].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 4 && beads[2][4].getFillColor() == Color::Transparent)
            beads[2][4].setFillColor(d1);
        else if (new_arr[0] == 0 && new_arr[1] == 3 && beads[0][3].getFillColor() == Color::Transparent)
            beads[0][3].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 3 && beads[2][3].getFillColor() == Color::Transparent)
            beads[2][3].setFillColor(d1);
        else if (new_arr[0] == 0 && new_arr[1] == 2 && beads[0][2].getFillColor() == Color::Transparent)
            beads[0][2].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 2 && beads[1][2].getFillColor() == Color::Transparent)
            beads[1][2].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 2 && beads[2][2].getFillColor() == Color::Transparent)
            beads[2][2].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 1 && beads[1][2].getFillColor() == d2 && beads[1][1].getFillColor() == Color::Transparent)
        {
            beads[1][1].setFillColor(d1);
            beads[1][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 3 && new_arr[1] == 1 && beads[2][2].getFillColor() == d2 && beads[3][1].getFillColor() == Color::Transparent)
        {
            beads[3][1].setFillColor(d1);
            beads[2][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 3 && new_arr[1] == 3 && beads[2][3].getFillColor() == d2 && beads[3][3].getFillColor() == Color::Transparent)
        {
            beads[3][3].setFillColor(d1);
            beads[2][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[1][3].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 1 && old_arr[1] == 4)
    {
        if (new_arr[0] == 0 && new_arr[1] == 4 && beads[0][4].getFillColor() == Color::Transparent)
            beads[0][4].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 4 && beads[2][4].getFillColor() == Color::Transparent)
            beads[2][4].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 3 && beads[1][3].getFillColor() == Color::Transparent)
            beads[1][3].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 2 && beads[1][3].getFillColor() == d2 && beads[1][2].getFillColor() == Color::Transparent)
        {
            beads[1][2].setFillColor(d1);
            beads[1][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 3 && new_arr[1] == 4 && beads[2][4].getFillColor() == d2 && beads[3][4].getFillColor() == Color::Transparent)
        {
            beads[3][4].setFillColor(d1);
            beads[2][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[1][4].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 2 && old_arr[1] == 0)
    {
        if (new_arr[0] == 1 && new_arr[1] == 0 && beads[1][0].getFillColor() == Color::Transparent)
            beads[1][0].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 0 && beads[3][0].getFillColor() == Color::Transparent)
            beads[3][0].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 1 && beads[1][1].getFillColor() == Color::Transparent)
            beads[1][1].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 1 && beads[2][1].getFillColor() == Color::Transparent)
            beads[2][1].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 1 && beads[3][1].getFillColor() == Color::Transparent)
            beads[3][1].setFillColor(d1);
        else if (new_arr[0] == 0 && new_arr[1] == 0 && beads[1][0].getFillColor() == d2 && beads[0][0].getFillColor() == Color::Transparent)
        {
            beads[0][0].setFillColor(d1);
            beads[1][0].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 4 && new_arr[1] == 0 && beads[3][0].getFillColor() == d2 && beads[4][0].getFillColor() == Color::Transparent)
        {
            beads[4][0].setFillColor(d1);
            beads[3][0].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 0 && new_arr[1] == 2 && beads[1][1].getFillColor() == d2 && beads[0][2].getFillColor() == Color::Transparent)
        {
            beads[0][2].setFillColor(d1);
            beads[1][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 2 && beads[2][1].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent)
        {
            beads[2][2].setFillColor(d1);
            beads[2][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 4 && new_arr[1] == 2 && beads[3][1].getFillColor() == d2 && beads[4][2].getFillColor() == Color::Transparent)
        {
            beads[4][2].setFillColor(d1);
            beads[3][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[2][0].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 2 && old_arr[1] == 1)
    {
        if (new_arr[0] == 1 && new_arr[1] == 1 && beads[1][1].getFillColor() == Color::Transparent)
            beads[1][1].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 0 && beads[2][0].getFillColor() == Color::Transparent)
            beads[2][0].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 1 && beads[3][1].getFillColor() == Color::Transparent)
            beads[3][1].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 2 && beads[2][2].getFillColor() == Color::Transparent)
            beads[2][2].setFillColor(d1);
        else if (new_arr[0] == 0 && new_arr[1] == 1 && beads[1][1].getFillColor() == d2 && beads[0][1].getFillColor() == Color::Transparent)
        {
            beads[0][1].setFillColor(d1);
            beads[1][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 3 && beads[2][2].getFillColor() == d2 && beads[2][3].getFillColor() == Color::Transparent)
        {
            beads[2][3].setFillColor(d1);
            beads[2][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 4 && new_arr[1] == 1 && beads[3][1].getFillColor() == d2 && beads[4][1].getFillColor() == Color::Transparent)
        {
            beads[4][1].setFillColor(d1);
            beads[3][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[2][1].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 2 && old_arr[1] == 2)
    {
        if (new_arr[0] == 1 && new_arr[1] == 1 && beads[1][1].getFillColor() == Color::Transparent)
            beads[1][1].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 1 && beads[2][1].getFillColor() == Color::Transparent)
            beads[2][1].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 1 && beads[3][1].getFillColor() == Color::Transparent)
            beads[3][1].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 2 && beads[1][2].getFillColor() == Color::Transparent)
            beads[1][2].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 2 && beads[3][2].getFillColor() == Color::Transparent)
            beads[3][2].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 3 && beads[1][3].getFillColor() == Color::Transparent)
            beads[1][3].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 3 && beads[2][3].getFillColor() == Color::Transparent)
            beads[2][3].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 3 && beads[3][3].getFillColor() == Color::Transparent)
            beads[3][3].setFillColor(d1);
        else if (new_arr[0] == 0 && new_arr[1] == 0 && beads[1][1].getFillColor() == d2 && beads[0][0].getFillColor() == Color::Transparent)
        {
            beads[0][0].setFillColor(d1);
            beads[1][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 0 && new_arr[1] == 2 && beads[1][2].getFillColor() == d2 && beads[0][2].getFillColor() == Color::Transparent)
        {
            beads[1][2].setFillColor(d1);
            beads[0][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 0 && new_arr[1] == 4 && beads[1][3].getFillColor() == d2 && beads[0][4].getFillColor() == Color::Transparent)
        {
            beads[0][4].setFillColor(d1);
            beads[1][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 0 && beads[2][1].getFillColor() == d2 && beads[2][0].getFillColor() == Color::Transparent)
        {
            beads[2][0].setFillColor(d1);
            beads[2][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 4 && beads[2][3].getFillColor() == d2 && beads[2][4].getFillColor() == Color::Transparent)
        {
            beads[2][4].setFillColor(d1);
            beads[2][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 4 && new_arr[1] == 0 && beads[3][1].getFillColor() == d2 && beads[4][0].getFillColor() == Color::Transparent)
        {
            beads[4][0].setFillColor(d1);
            beads[3][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 4 && new_arr[1] == 2 && beads[3][2].getFillColor() == d2 && beads[4][2].getFillColor() == Color::Transparent)
        {
            beads[4][2].setFillColor(d1);
            beads[3][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 4 && new_arr[1] == 4 && beads[3][3].getFillColor() == d2 && beads[4][4].getFillColor() == Color::Transparent)
        {
            beads[4][4].setFillColor(d1);
            beads[3][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[2][2].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 2 && old_arr[1] == 3)
    {
        if (new_arr[0] == 1 && new_arr[1] == 3 && beads[1][3].getFillColor() == Color::Transparent)
            beads[1][3].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 4 && beads[2][4].getFillColor() == Color::Transparent)
            beads[2][4].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 3 && beads[3][3].getFillColor() == Color::Transparent)
            beads[3][3].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 2 && beads[2][2].getFillColor() == Color::Transparent)
            beads[2][2].setFillColor(d1);
        else if (new_arr[0] == 0 && new_arr[1] == 3 && beads[1][3].getFillColor() == d2 && beads[0][3].getFillColor() == Color::Transparent)
        {
            beads[0][3].setFillColor(d1);
            beads[1][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 1 && beads[2][2].getFillColor() == d2 && beads[2][1].getFillColor() == Color::Transparent)
        {
            beads[2][1].setFillColor(d1);
            beads[2][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 4 && new_arr[1] == 3 && beads[3][3].getFillColor() == d2 && beads[4][3].getFillColor() == Color::Transparent)
        {
            beads[4][3].setFillColor(d1);
            beads[3][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[2][3].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 2 && old_arr[1] == 4)
    {
        if (new_arr[0] == 1 && new_arr[1] == 4 && beads[1][4].getFillColor() == Color::Transparent)
            beads[1][4].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 4 && beads[3][4].getFillColor() == Color::Transparent)
            beads[3][4].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 3 && beads[1][3].getFillColor() == Color::Transparent)
            beads[1][3].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 3 && beads[2][3].getFillColor() == Color::Transparent)
            beads[2][3].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 3 && beads[3][3].getFillColor() == Color::Transparent)
            beads[3][3].setFillColor(d1);
        else if (new_arr[0] == 0 && new_arr[1] == 4 && beads[1][4].getFillColor() == d2 && beads[0][4].getFillColor() == Color::Transparent)
        {
            beads[0][4].setFillColor(d1);
            beads[1][4].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 4 && new_arr[1] == 4 && beads[3][4].getFillColor() == d2 && beads[4][4].getFillColor() == Color::Transparent)
        {
            beads[4][4].setFillColor(d1);
            beads[3][4].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 0 && new_arr[1] == 2 && beads[1][3].getFillColor() == d2 && beads[0][2].getFillColor() == Color::Transparent)
        {
            beads[0][2].setFillColor(d1);
            beads[1][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 2 && beads[2][3].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent)
        {
            beads[2][2].setFillColor(d1);
            beads[2][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 4 && new_arr[1] == 2 && beads[3][3].getFillColor() == d2 && beads[4][2].getFillColor() == Color::Transparent)
        {
            beads[4][2].setFillColor(d1);
            beads[3][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[2][4].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 3 && old_arr[1] == 0)
    {
        if (new_arr[0] == 4 && new_arr[1] == 0 && beads[4][0].getFillColor() == Color::Transparent)
            beads[4][0].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 0 && beads[2][0].getFillColor() == Color::Transparent)
            beads[2][0].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 1 && beads[3][1].getFillColor() == Color::Transparent)
            beads[3][1].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 2 && beads[3][1].getFillColor() == d2 && beads[3][2].getFillColor() == Color::Transparent)
        {
            beads[3][2].setFillColor(d1);
            beads[3][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 1 && new_arr[1] == 0 && beads[2][0].getFillColor() == d2 && beads[1][0].getFillColor() == Color::Transparent)
        {
            beads[1][0].setFillColor(d1);
            beads[2][0].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[3][0].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 3 && old_arr[1] == 1)
    {
        if (new_arr[0] == 4 && new_arr[1] == 0 && beads[4][0].getFillColor() == Color::Transparent)
            beads[4][0].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 0 && beads[3][0].getFillColor() == Color::Transparent)
            beads[3][0].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 0 && beads[2][0].getFillColor() == Color::Transparent)
            beads[2][0].setFillColor(d1);
        else if (new_arr[0] == 4 && new_arr[1] == 1 && beads[4][1].getFillColor() == Color::Transparent)
            beads[4][1].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 1 && beads[2][1].getFillColor() == Color::Transparent)
            beads[2][1].setFillColor(d1);
        else if (new_arr[0] == 4 && new_arr[1] == 2 && beads[4][2].getFillColor() == Color::Transparent)
            beads[4][2].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 2 && beads[3][2].getFillColor() == Color::Transparent)
            beads[3][2].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 2 && beads[2][2].getFillColor() == Color::Transparent)
            beads[2][2].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 3 && beads[3][2].getFillColor() == d2 && beads[3][3].getFillColor() == Color::Transparent)
        {
            beads[3][3].setFillColor(d1);
            beads[3][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 1 && new_arr[1] == 1 && beads[2][1].getFillColor() == d2 && beads[1][1].getFillColor() == Color::Transparent)
        {
            beads[1][1].setFillColor(d1);
            beads[2][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 1 && new_arr[1] == 3 && beads[2][2].getFillColor() == d2 && beads[1][3].getFillColor() == Color::Transparent)
        {
            beads[1][3].setFillColor(d1);
            beads[2][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[3][1].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 3 && old_arr[1] == 2)
    {
        if (new_arr[0] == 4 && new_arr[1] == 2 && beads[4][2].getFillColor() == Color::Transparent)
            beads[4][2].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 1 && beads[3][1].getFillColor() == Color::Transparent)
            beads[3][1].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 2 && beads[2][2].getFillColor() == Color::Transparent)
            beads[2][2].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 3 && beads[3][3].getFillColor() == Color::Transparent)
            beads[3][3].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 0 && beads[3][1].getFillColor() == d2 && beads[3][0].getFillColor() == Color::Transparent)
        {
            beads[3][0].setFillColor(d1);
            beads[3][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 1 && new_arr[1] == 2 && beads[2][2].getFillColor() == d2 && beads[1][2].getFillColor() == Color::Transparent)
        {
            beads[1][2].setFillColor(d1);
            beads[2][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 3 && new_arr[1] == 4 && beads[3][3].getFillColor() == d2 && beads[3][4].getFillColor() == Color::Transparent)
        {
            beads[3][4].setFillColor(d1);
            beads[3][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[3][2].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 3 && old_arr[1] == 3)
    {
        if (new_arr[0] == 4 && new_arr[1] == 4 && beads[4][4].getFillColor() == Color::Transparent)
            beads[4][4].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 4 && beads[3][4].getFillColor() == Color::Transparent)
            beads[3][4].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 4 && beads[2][4].getFillColor() == Color::Transparent)
            beads[2][4].setFillColor(d1);
        else if (new_arr[0] == 4 && new_arr[1] == 3 && beads[4][3].getFillColor() == Color::Transparent)
            beads[4][3].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 3 && beads[2][3].getFillColor() == Color::Transparent)
            beads[2][3].setFillColor(d1);
        else if (new_arr[0] == 4 && new_arr[1] == 2 && beads[4][2].getFillColor() == Color::Transparent)
            beads[4][2].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 2 && beads[3][2].getFillColor() == Color::Transparent)
            beads[3][2].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 2 && beads[2][2].getFillColor() == Color::Transparent)
            beads[2][2].setFillColor(d1);
        else if (new_arr[0] == 1 && new_arr[1] == 1 && beads[2][2].getFillColor() == d2 && beads[1][1].getFillColor() == Color::Transparent)
        {
            beads[1][1].setFillColor(d1);
            beads[2][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 3 && new_arr[1] == 1 && beads[3][2].getFillColor() == d2 && beads[3][1].getFillColor() == Color::Transparent)
        {
            beads[3][1].setFillColor(d1);
            beads[3][2].setFillColor(Color::Transparent);
            check = 1;

        }
        else if (new_arr[0] == 1 && new_arr[1] == 3 && beads[2][3].getFillColor() == d2 && beads[1][3].getFillColor() == Color::Transparent)
        {
            beads[1][3].setFillColor(d1);
            beads[2][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[3][3].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 3 && old_arr[1] == 4)
    {
        if (new_arr[0] == 4 && new_arr[1] == 4 && beads[4][4].getFillColor() == Color::Transparent)
            beads[4][4].setFillColor(d1);
        else if (new_arr[0] == 2 && new_arr[1] == 4 && beads[2][4].getFillColor() == Color::Transparent)
            beads[2][4].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 3 && beads[3][3].getFillColor() == Color::Transparent)
            beads[3][3].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 2 && beads[3][3].getFillColor() == d2 && beads[3][2].getFillColor() == Color::Transparent)
        {
            beads[3][2].setFillColor(d1);
            beads[3][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 1 && new_arr[1] == 4 && beads[2][4].getFillColor() == d2 && beads[3][4].getFillColor() == Color::Transparent)
        {
            beads[3][4].setFillColor(d1);
            beads[2][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[3][4].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 4 && old_arr[1] == 0)
    {
        if (new_arr[0] == 4 && new_arr[1] == 1 && beads[4][1].getFillColor() == Color::Transparent)
            beads[4][1].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 1 && beads[3][1].getFillColor() == Color::Transparent)
            beads[3][1].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 0 && beads[3][0].getFillColor() == Color::Transparent)
            beads[3][0].setFillColor(d1);
        else if (new_arr[0] == 4 && new_arr[1] == 2 && beads[4][1].getFillColor() == d2 && beads[4][2].getFillColor() == Color::Transparent)
        {
            beads[4][2].setFillColor(d1);
            beads[4][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 2 && beads[3][1].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent)
        {
            beads[2][2].setFillColor(d1);
            beads[3][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 0 && beads[3][0].getFillColor() == d2 && beads[2][0].getFillColor() == Color::Transparent)
        {
            beads[2][0].setFillColor(d1);
            beads[3][0].setFillColor(d2);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[4][0].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 4 && old_arr[1] == 1)
    {
        if (new_arr[0] == 4 && new_arr[1] == 0 && beads[4][0].getFillColor() == Color::Transparent)
            beads[4][0].setFillColor(d1);
        else if (new_arr[0] == 4 && new_arr[1] == 2 && beads[4][2].getFillColor() == Color::Transparent)
            beads[4][2].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 1 && beads[3][1].getFillColor() == Color::Transparent)
            beads[3][1].setFillColor(d1);
        else if (new_arr[0] == 4 && new_arr[1] == 3 && beads[4][2].getFillColor() == d2 && beads[4][3].getFillColor() == Color::Transparent)
        {
            beads[4][3].setFillColor(d1);
            beads[4][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 1 && beads[3][1].getFillColor() == d2 && beads[2][1].getFillColor() == Color::Transparent)
        {
            beads[2][1].setFillColor(d1);
            beads[3][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[4][1].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 4 && old_arr[1] == 2)
    {
        if (new_arr[0] == 4 && new_arr[1] == 1 && beads[4][1].getFillColor() == Color::Transparent)
            beads[4][1].setFillColor(d1);
        else if (new_arr[0] == 4 && new_arr[1] == 3 && beads[4][3].getFillColor() == Color::Transparent)
            beads[4][3].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 1 && beads[3][1].getFillColor() == Color::Transparent)
            beads[3][1].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 2 && beads[3][2].getFillColor() == Color::Transparent)
            beads[3][2].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 3 && beads[3][3].getFillColor() == Color::Transparent)
            beads[3][3].setFillColor(d1);
        else if (new_arr[0] == 4 && new_arr[1] == 0 && beads[4][1].getFillColor() == d2 && beads[4][0].getFillColor() == Color::Transparent)
        {
            beads[4][0].setFillColor(d1);
            beads[4][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 4 && new_arr[1] == 4 && beads[4][3].getFillColor() == d2 && beads[4][4].getFillColor() == Color::Transparent)
        {
            beads[4][4].setFillColor(d1);
            beads[4][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 0 && beads[3][1].getFillColor() == d2 && beads[2][0].getFillColor() == Color::Transparent)
        {
            beads[2][0].setFillColor(d1);
            beads[3][1].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 2 && beads[3][2].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent)
        {
            beads[2][2].setFillColor(d1);
            beads[3][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 4 && beads[3][3].getFillColor() == d2 && beads[2][4].getFillColor() == Color::Transparent)
        {
            beads[2][4].setFillColor(d1);
            beads[3][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[4][2].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 4 && old_arr[1] == 3)
    {
        if (new_arr[0] == 4 && new_arr[1] == 2 && beads[4][2].getFillColor() == Color::Transparent)
            beads[4][2].setFillColor(d1);
        else if (new_arr[0] == 4 && new_arr[1] == 4 && beads[4][4].getFillColor() == Color::Transparent)
            beads[4][4].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 3 && beads[3][3].getFillColor() == Color::Transparent)
            beads[3][3].setFillColor(d1);
        else if (new_arr[0] == 4 && new_arr[1] == 1 && beads[4][2].getFillColor() == d2 && beads[4][1].getFillColor() == Color::Transparent)
        {
            beads[4][1].setFillColor(d1);
            beads[4][2].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 3 && beads[3][3].getFillColor() == d2 && beads[2][3].getFillColor() == Color::Transparent)
        {
            beads[2][3].setFillColor(d1);
            beads[3][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[4][3].setFillColor(Color::Transparent);
        return true;
    }
    else if (old_arr[0] == 4 && old_arr[1] == 4)
    {
        if (new_arr[0] == 4 && new_arr[1] == 3 && beads[4][3].getFillColor() == Color::Transparent)
            beads[4][3].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 3 && beads[3][3].getFillColor() == Color::Transparent)
            beads[3][3].setFillColor(d1);
        else if (new_arr[0] == 3 && new_arr[1] == 4 && beads[3][4].getFillColor() == Color::Transparent)
            beads[3][4].setFillColor(d1);
        else if (new_arr[0] == 4 && new_arr[1] == 2 && beads[4][3].getFillColor() == d2 && beads[4][2].getFillColor() == Color::Transparent)
        {
            beads[4][2].setFillColor(d1);
            beads[4][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 2 && beads[3][3].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent)
        {
            beads[2][2].setFillColor(d1);
            beads[3][3].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else if (new_arr[0] == 2 && new_arr[1] == 4 && beads[3][4].getFillColor() == d2 && beads[2][4].getFillColor() == Color::Transparent)
        {
            beads[2][4].setFillColor(d1);
            beads[3][4].setFillColor(Color::Transparent);
            check = 1;
            bead--;
        }
        else
            return false;
        beads[4][4].setFillColor(Color::Transparent);
        return true;
    }
    else
        return false;
}

bool moveCheck1(int old_arr[])
{
    if ((old_arr[0]<5 && old_arr[0] > -1) || (old_arr[1]<5 && old_arr[1] > -1))
        return true;
    else
        return false;

}

bool moveCheck2(int old_arr[], Color d1)
{
    if ((old_arr[0] == 0 && old_arr[1] == 0 && beads[0][0].getFillColor() == d1) || (old_arr[0] == 1 && old_arr[1] == 0 && beads[1][0].getFillColor() == d1) || (old_arr[0] == 2 && old_arr[1] == 0 && beads[2][0].getFillColor() == d1) || (old_arr[0] == 3 && old_arr[1] == 0 && beads[3][0].getFillColor() == d1) || (old_arr[0] == 4 && old_arr[1] == 0 && beads[4][0].getFillColor() == d1) || (old_arr[0] == 0 && old_arr[1] == 1 && beads[0][1].getFillColor() == d1) || (old_arr[0] == 1 && old_arr[1] == 1 && beads[1][1].getFillColor() == d1) || (old_arr[0] == 2 && old_arr[1] == 1 && beads[2][1].getFillColor() == d1) || (old_arr[0] == 3 && old_arr[1] == 1 && beads[3][1].getFillColor() == d1) || (old_arr[0] == 4 && old_arr[1] == 1 && beads[4][1].getFillColor() == d1) || (old_arr[0] == 0 && old_arr[1] == 2 && beads[0][2].getFillColor() == d1) || (old_arr[0] == 1 && old_arr[1] == 2 && beads[1][2].getFillColor() == d1) || (old_arr[0] == 2 && old_arr[1] == 2 && beads[2][2].getFillColor() == d1) || (old_arr[0] == 3 && old_arr[1] == 2 && beads[3][2].getFillColor() == d1) || (old_arr[0] == 4 && old_arr[1] == 2 && beads[4][2].getFillColor() == d1) || (old_arr[0] == 0 && old_arr[1] == 3 && beads[0][3].getFillColor() == d1) || (old_arr[0] == 1 && old_arr[1] == 3 && beads[1][3].getFillColor() == d1) || (old_arr[0] == 2 && old_arr[1] == 3 && beads[2][3].getFillColor() == d1) || (old_arr[0] == 3 && old_arr[1] == 3 && beads[3][3].getFillColor() == d1) || (old_arr[0] == 4 && old_arr[1] == 3 && beads[4][3].getFillColor() == d1) || (old_arr[0] == 0 && old_arr[1] == 4 && beads[0][4].getFillColor() == d1) || (old_arr[0] == 1 && old_arr[1] == 4 && beads[1][4].getFillColor() == d1) || (old_arr[0] == 2 && old_arr[1] == 4 && beads[2][4].getFillColor() == d1) || (old_arr[0] == 3 && old_arr[1] == 4 && beads[3][4].getFillColor() == d1) || (old_arr[0] == 4 && old_arr[1] == 4 && beads[4][4].getFillColor() == d1))
        return true;
    else
        return false;
}

bool moveCheck3(int old_arr[], Color d1, Color d2)
{
    if (old_arr[0] == 0 && old_arr[1] == 0)
    {
        if (beads[0][1].getFillColor() == Color::Transparent || beads[1][1].getFillColor() == Color::Transparent || beads[1][0].getFillColor() == Color::Transparent || (beads[0][1].getFillColor() == d2 && beads[0][2].getFillColor() == Color::Transparent) || (beads[1][1].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent) || (beads[1][0].getFillColor() == d2 && beads[2][0].getFillColor() == Color::Transparent))
            return true;
    }
    else if (old_arr[0] == 0 && old_arr[1] == 1)
    {
        if (beads[0][0].getFillColor() == Color::Transparent || beads[0][2].getFillColor() == Color::Transparent || beads[1][1].getFillColor() == Color::Transparent || (beads[0][2].getFillColor() == d2 && beads[0][3].getFillColor() == Color::Transparent) || (beads[1][1].getFillColor() == d2 && beads[2][1].getFillColor() == Color::Transparent))
            return true;

    }
    else if (old_arr[0] == 0 && old_arr[1] == 2)
    {
        if (beads[0][1].getFillColor() == Color::Transparent || beads[0][3].getFillColor() == Color::Transparent || beads[1][1].getFillColor() == Color::Transparent || beads[1][2].getFillColor() == Color::Transparent || beads[1][3].getFillColor() == Color::Transparent || (beads[0][1].getFillColor() == d2 && beads[0][0].getFillColor() == Color::Transparent) || (beads[0][3].getFillColor() == d2 && beads[0][4].getFillColor() == Color::Transparent) || (beads[1][1].getFillColor() == d2 && beads[2][0].getFillColor() == Color::Transparent) || (beads[1][2].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent) || (beads[1][3].getFillColor() == d2 && beads[2][4].getFillColor() == Color::Transparent))
            return true;
    }
    else if (old_arr[0] == 0 && old_arr[1] == 3)
    {
        if (beads[0][2].getFillColor() == Color::Transparent || beads[0][4].getFillColor() == Color::Transparent || beads[1][3].getFillColor() == Color::Transparent || (beads[0][2].getFillColor() == d2 && beads[0][1].getFillColor() == Color::Transparent) || (beads[1][3].getFillColor() == d2 && beads[2][3].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 0 && old_arr[1] == 4)
    {
        if (beads[0][3].getFillColor() == Color::Transparent || beads[1][3].getFillColor() == Color::Transparent || beads[1][4].getFillColor() == Color::Transparent || (beads[0][3].getFillColor() == d2 && beads[0][2].getFillColor() == Color::Transparent) || (beads[1][3].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent) || (beads[1][4].getFillColor() == d2 && beads[2][4].getFillColor() == Color::Transparent))
            return true;
    }
    else if (old_arr[0] == 1 && old_arr[1] == 0)
    {
        if (beads[0][0].getFillColor() == Color::Transparent || beads[2][0].getFillColor() == Color::Transparent || beads[1][1].getFillColor() == Color::Transparent || (beads[1][1].getFillColor() == d2 && beads[1][2].getFillColor() == Color::Transparent) || (beads[2][0].getFillColor() == d2 && beads[3][0].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 1 && old_arr[1] == 1)
    {
        if (beads[0][0].getFillColor() == Color::Transparent || beads[1][0].getFillColor() == Color::Transparent || beads[2][0].getFillColor() == Color::Transparent || beads[0][1].getFillColor() == Color::Transparent || beads[2][1].getFillColor() == Color::Transparent || beads[0][2].getFillColor() == Color::Transparent || beads[1][2].getFillColor() == Color::Transparent || beads[2][2].getFillColor() == Color::Transparent || (beads[1][2].getFillColor() == d2 && beads[1][3].getFillColor() == Color::Transparent) || (beads[2][1].getFillColor() == d2 && beads[3][1].getFillColor() == Color::Transparent) || (beads[2][2].getFillColor() == d2 && beads[3][3].getFillColor() == Color::Transparent))
            return true;
    }
    else if (old_arr[0] == 1 && old_arr[1] == 2)
    {
        if (beads[0][2].getFillColor() == Color::Transparent || beads[1][1].getFillColor() == Color::Transparent || beads[2][2].getFillColor() == Color::Transparent || beads[1][3].getFillColor() == Color::Transparent || (beads[1][1].getFillColor() == d2 && beads[1][0].getFillColor() == Color::Transparent) || (beads[2][2].getFillColor() == d2 && beads[3][2].getFillColor() == Color::Transparent) || (beads[1][3].getFillColor() == d2 && beads[1][4].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 1 && old_arr[1] == 3)
    {
        if (beads[0][4].getFillColor() == Color::Transparent || beads[1][4].getFillColor() == Color::Transparent || beads[2][4].getFillColor() == Color::Transparent || beads[0][3].getFillColor() == Color::Transparent || beads[2][3].getFillColor() == Color::Transparent || beads[0][2].getFillColor() == Color::Transparent || beads[1][2].getFillColor() == Color::Transparent || beads[2][2].getFillColor() == Color::Transparent || (beads[1][2].getFillColor() == d2 && beads[1][1].getFillColor() == Color::Transparent) || (beads[2][2].getFillColor() == d2 && beads[3][1].getFillColor() == Color::Transparent) || (beads[2][3].getFillColor() == d2 && beads[3][3].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 1 && old_arr[1] == 4)
    {
        if (beads[0][4].getFillColor() == Color::Transparent || beads[2][4].getFillColor() == Color::Transparent || beads[1][3].getFillColor() == Color::Transparent || (beads[1][3].getFillColor() == d2 && beads[1][2].getFillColor() == Color::Transparent) || (beads[2][4].getFillColor() == d2 && beads[3][4].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 2 && old_arr[1] == 0)
    {
        if (beads[1][0].getFillColor() == Color::Transparent || beads[3][0].getFillColor() == Color::Transparent || beads[1][1].getFillColor() == Color::Transparent || beads[2][1].getFillColor() == Color::Transparent || beads[3][1].getFillColor() == Color::Transparent || (beads[1][0].getFillColor() == d2 && beads[0][0].getFillColor() == Color::Transparent) || (beads[3][0].getFillColor() == d2 && beads[4][0].getFillColor() == Color::Transparent) || (beads[1][1].getFillColor() == d2 && beads[0][2].getFillColor() == Color::Transparent) || (beads[2][1].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent) || (beads[3][1].getFillColor() == d2 && beads[4][2].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 2 && old_arr[1] == 1)
    {
        if (beads[1][1].getFillColor() == Color::Transparent || beads[2][0].getFillColor() == Color::Transparent || beads[3][1].getFillColor() == Color::Transparent || beads[2][2].getFillColor() == Color::Transparent || (beads[1][1].getFillColor() == d2 && beads[0][1].getFillColor() == Color::Transparent) || (beads[2][2].getFillColor() == d2 && beads[2][3].getFillColor() == Color::Transparent) || (beads[3][1].getFillColor() == d2 && beads[4][1].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 2 && old_arr[1] == 2)
    {
        if (beads[1][1].getFillColor() == Color::Transparent || beads[2][1].getFillColor() == Color::Transparent || beads[3][1].getFillColor() == Color::Transparent || beads[1][2].getFillColor() == Color::Transparent || beads[3][2].getFillColor() == Color::Transparent || beads[1][3].getFillColor() == Color::Transparent || beads[2][3].getFillColor() == Color::Transparent || beads[3][3].getFillColor() == Color::Transparent || (beads[1][1].getFillColor() == d2 && beads[0][0].getFillColor() == Color::Transparent) || (beads[1][2].getFillColor() == d2 && beads[0][2].getFillColor() == Color::Transparent) || (beads[1][3].getFillColor() == d2 && beads[0][4].getFillColor() == Color::Transparent) || (beads[2][1].getFillColor() == d2 && beads[2][0].getFillColor() == Color::Transparent) || (beads[2][3].getFillColor() == d2 && beads[2][4].getFillColor() == Color::Transparent) || (beads[3][1].getFillColor() == d2 && beads[4][0].getFillColor() == Color::Transparent) || (beads[3][2].getFillColor() == d2 && beads[4][2].getFillColor() == Color::Transparent) || (beads[3][3].getFillColor() == d2 && beads[4][4].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 2 && old_arr[1] == 3)
    {
        if (beads[1][3].getFillColor() == Color::Transparent || beads[2][4].getFillColor() == Color::Transparent || beads[3][3].getFillColor() == Color::Transparent || beads[2][2].getFillColor() == Color::Transparent || (beads[1][3].getFillColor() == d2 && beads[0][3].getFillColor() == Color::Transparent) || (beads[2][2].getFillColor() == d2 && beads[2][1].getFillColor() == Color::Transparent) || (beads[3][3].getFillColor() == d2 && beads[4][3].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 2 && old_arr[1] == 4)
    {
        if (beads[1][4].getFillColor() == Color::Transparent || beads[3][4].getFillColor() == Color::Transparent || beads[1][3].getFillColor() == Color::Transparent || beads[2][3].getFillColor() == Color::Transparent || beads[3][3].getFillColor() == Color::Transparent || (beads[1][4].getFillColor() == d2 && beads[0][4].getFillColor() == Color::Transparent) || (beads[3][4].getFillColor() == d2 && beads[4][4].getFillColor() == Color::Transparent) || (beads[1][3].getFillColor() == d2 && beads[0][2].getFillColor() == Color::Transparent) || (beads[2][3].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent) || (beads[3][3].getFillColor() == d2 && beads[4][2].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 3 && old_arr[1] == 0)
    {
        if (beads[4][0].getFillColor() == Color::Transparent || beads[2][0].getFillColor() == Color::Transparent || beads[3][1].getFillColor() == Color::Transparent || (beads[3][1].getFillColor() == d2 && beads[3][2].getFillColor() == Color::Transparent) || (beads[2][0].getFillColor() == d2 && beads[1][0].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 3 && old_arr[1] == 1)
    {
        if (beads[4][0].getFillColor() == Color::Transparent || beads[3][0].getFillColor() == Color::Transparent || beads[2][0].getFillColor() == Color::Transparent || beads[4][1].getFillColor() == Color::Transparent || beads[2][1].getFillColor() == Color::Transparent || beads[4][2].getFillColor() == Color::Transparent || beads[3][2].getFillColor() == Color::Transparent || beads[2][2].getFillColor() == Color::Transparent || (beads[3][2].getFillColor() == d2 && beads[3][3].getFillColor() == Color::Transparent) || (beads[2][1].getFillColor() == d2 && beads[1][1].getFillColor() == Color::Transparent) || (beads[2][2].getFillColor() == d2 && beads[1][3].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 3 && old_arr[1] == 2)
    {
        if (beads[4][2].getFillColor() == Color::Transparent || beads[3][1].getFillColor() == Color::Transparent || beads[2][2].getFillColor() == Color::Transparent || beads[3][3].getFillColor() == Color::Transparent || (beads[3][1].getFillColor() == d2 && beads[3][0].getFillColor() == Color::Transparent) || (beads[2][2].getFillColor() == d2 && beads[1][2].getFillColor() == Color::Transparent) || (beads[3][3].getFillColor() == d2 && beads[3][4].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 3 && old_arr[1] == 3)
    {
        if (beads[4][4].getFillColor() == Color::Transparent || beads[3][4].getFillColor() == Color::Transparent || beads[2][4].getFillColor() == Color::Transparent || beads[4][3].getFillColor() == Color::Transparent || beads[2][3].getFillColor() == Color::Transparent || beads[4][2].getFillColor() == Color::Transparent || beads[3][2].getFillColor() == Color::Transparent || beads[2][2].getFillColor() == Color::Transparent || (beads[2][2].getFillColor() == d2 && beads[1][1].getFillColor() == Color::Transparent) || (beads[3][2].getFillColor() == d2 && beads[3][1].getFillColor() == Color::Transparent) || (beads[2][3].getFillColor() == d2 && beads[1][3].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 3 && old_arr[1] == 4)
    {
        if (beads[4][4].getFillColor() == Color::Transparent || beads[2][4].getFillColor() == Color::Transparent || beads[3][3].getFillColor() == Color::Transparent || (beads[3][3].getFillColor() == d2 && beads[3][2].getFillColor() == Color::Transparent) || (beads[2][4].getFillColor() == d2 && beads[3][4].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 4 && old_arr[1] == 0)
    {
        if (beads[4][1].getFillColor() == Color::Transparent || beads[3][1].getFillColor() == Color::Transparent || beads[3][0].getFillColor() == Color::Transparent || (beads[4][1].getFillColor() == d2 && beads[4][2].getFillColor() == Color::Transparent) || (beads[3][1].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent) || (beads[3][0].getFillColor() == d2 && beads[2][0].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 4 && old_arr[1] == 1)
    {
        if (beads[4][0].getFillColor() == Color::Transparent || beads[4][2].getFillColor() == Color::Transparent || beads[3][1].getFillColor() == Color::Transparent || (beads[4][2].getFillColor() == d2 && beads[4][3].getFillColor() == Color::Transparent) || (beads[3][1].getFillColor() == d2 && beads[2][1].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 4 && old_arr[1] == 2)
    {
        if (beads[4][1].getFillColor() == Color::Transparent || beads[4][3].getFillColor() == Color::Transparent || beads[3][1].getFillColor() == Color::Transparent || beads[3][2].getFillColor() == Color::Transparent || beads[3][3].getFillColor() == Color::Transparent || (beads[4][1].getFillColor() == d2 && beads[4][0].getFillColor() == Color::Transparent) || (beads[4][3].getFillColor() == d2 && beads[4][4].getFillColor() == Color::Transparent) || (beads[3][1].getFillColor() == d2 && beads[2][0].getFillColor() == Color::Transparent) || (beads[3][2].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent) || (beads[3][3].getFillColor() == d2 && beads[2][4].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 4 && old_arr[1] == 3)
    {
        if (beads[4][2].getFillColor() == Color::Transparent || beads[4][4].getFillColor() == Color::Transparent || beads[3][3].getFillColor() == Color::Transparent || (beads[4][2].getFillColor() == d2 && beads[4][1].getFillColor() == Color::Transparent) || (beads[3][3].getFillColor() == d2 && beads[2][3].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 4 && old_arr[1] == 4)
    {
        if (beads[4][3].getFillColor() == Color::Transparent || beads[3][3].getFillColor() == Color::Transparent || beads[3][4].getFillColor() == Color::Transparent || (beads[4][3].getFillColor() == d2 && beads[4][2].getFillColor() == Color::Transparent) || (beads[3][3].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent) || (beads[3][4].getFillColor() == d2 && beads[2][4].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else
        return false;

}

bool moveToNextPos(int old_arr[], Color d1, Color d2)
{// to check k agaye tu koi bead nhi mar rha if yes tu ye chance de rha 
    if (old_arr[0] == 0 && old_arr[1] == 0)
    {
        if ((beads[0][1].getFillColor() == d2 && beads[0][2].getFillColor() == Color::Transparent) || (beads[1][1].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent) || (beads[1][0].getFillColor() == d2 && beads[2][0].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 0 && old_arr[1] == 1)
    {
        if ((beads[0][2].getFillColor() == d2 && beads[0][3].getFillColor() == Color::Transparent) || (beads[1][1].getFillColor() == d2 && beads[2][1].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 0 && old_arr[1] == 2)
    {
        if ((beads[0][1].getFillColor() == d2 && beads[0][0].getFillColor() == Color::Transparent) || (beads[0][3].getFillColor() == d2 && beads[0][4].getFillColor() == Color::Transparent) || (beads[1][1].getFillColor() == d2 && beads[2][0].getFillColor() == Color::Transparent) || (beads[1][2].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent) || (beads[1][3].getFillColor() == d2 && beads[2][4].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 0 && old_arr[1] == 3)
    {
        if ((beads[0][2].getFillColor() == d2 && beads[0][1].getFillColor() == Color::Transparent) || (beads[1][3].getFillColor() == d2 && beads[2][3].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 0 && old_arr[1] == 4)
    {
        if ((beads[0][3].getFillColor() == d2 && beads[0][2].getFillColor() == Color::Transparent) || (beads[1][3].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent) || (beads[1][4].getFillColor() == d2 && beads[2][4].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 1 && old_arr[1] == 0)
    {
        if ((beads[1][1].getFillColor() == d2 && beads[1][2].getFillColor() == Color::Transparent) || (beads[2][0].getFillColor() == d2 && beads[3][0].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 1 && old_arr[1] == 1)
    {
        if ((beads[1][2].getFillColor() == d2 && beads[1][3].getFillColor() == Color::Transparent) || (beads[2][1].getFillColor() == d2 && beads[3][1].getFillColor() == Color::Transparent) || (beads[2][2].getFillColor() == d2 && beads[3][3].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 1 && old_arr[1] == 2)
    {
        if ((beads[1][1].getFillColor() == d2 && beads[1][0].getFillColor() == Color::Transparent) || (beads[2][2].getFillColor() == d2 && beads[3][2].getFillColor() == Color::Transparent) || (beads[1][3].getFillColor() == d2 && beads[1][4].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 1 && old_arr[1] == 3)
    {
        if ((beads[1][2].getFillColor() == d2 && beads[1][1].getFillColor() == Color::Transparent) || (beads[2][2].getFillColor() == d2 && beads[3][1].getFillColor() == Color::Transparent) || (beads[2][3].getFillColor() == d2 && beads[3][3].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 1 && old_arr[1] == 4)
    {
        if ((beads[1][3].getFillColor() == d2 && beads[1][2].getFillColor() == Color::Transparent) || (beads[2][4].getFillColor() == d2 && beads[3][4].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 2 && old_arr[1] == 0)
    {
        if ((beads[1][0].getFillColor() == d2 && beads[0][0].getFillColor() == Color::Transparent) || (beads[3][0].getFillColor() == d2 && beads[4][0].getFillColor() == Color::Transparent) || (beads[1][1].getFillColor() == d2 && beads[0][2].getFillColor() == Color::Transparent) || (beads[2][1].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent) || (beads[3][1].getFillColor() == d2 && beads[4][2].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 2 && old_arr[1] == 1)
    {
        if ((beads[1][1].getFillColor() == d2 && beads[0][1].getFillColor() == Color::Transparent) || (beads[2][2].getFillColor() == d2 && beads[2][3].getFillColor() == Color::Transparent) || (beads[3][1].getFillColor() == d2 && beads[4][1].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 2 && old_arr[1] == 2)
    {
        if ((beads[1][1].getFillColor() == d2 && beads[0][0].getFillColor() == Color::Transparent) || (beads[1][2].getFillColor() == d2 && beads[0][2].getFillColor() == Color::Transparent) || (beads[1][3].getFillColor() == d2 && beads[0][4].getFillColor() == Color::Transparent) || (beads[2][1].getFillColor() == d2 && beads[2][0].getFillColor() == Color::Transparent) || (beads[2][3].getFillColor() == d2 && beads[2][4].getFillColor() == Color::Transparent) || (beads[3][1].getFillColor() == d2 && beads[4][0].getFillColor() == Color::Transparent) || (beads[3][2].getFillColor() == d2 && beads[4][2].getFillColor() == Color::Transparent) || (beads[3][3].getFillColor() == d2 && beads[4][4].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 2 && old_arr[1] == 3)
    {
        if ((beads[1][3].getFillColor() == d2 && beads[0][3].getFillColor() == Color::Transparent) || (beads[2][2].getFillColor() == d2 && beads[2][1].getFillColor() == Color::Transparent) || (beads[3][3].getFillColor() == d2 && beads[4][3].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 2 && old_arr[1] == 4)
    {
        if ((beads[1][4].getFillColor() == d2 && beads[0][4].getFillColor() == Color::Transparent) || (beads[3][4].getFillColor() == d2 && beads[4][4].getFillColor() == Color::Transparent) || (beads[1][3].getFillColor() == d2 && beads[0][2].getFillColor() == Color::Transparent) || (beads[2][3].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent) || (beads[3][3].getFillColor() == d2 && beads[4][2].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 3 && old_arr[1] == 0)
    {
        if ((beads[3][1].getFillColor() == d2 && beads[3][2].getFillColor() == Color::Transparent) || (beads[2][0].getFillColor() == d2 && beads[1][0].getFillColor() == Color::Transparent))
            return 0;
        else
            return false;
    }
    else if (old_arr[0] == 3 && old_arr[1] == 1)
    {
        if ((beads[3][2].getFillColor() == d2 && beads[3][3].getFillColor() == Color::Transparent) || (beads[2][1].getFillColor() == d2 && beads[1][1].getFillColor() == Color::Transparent) || (beads[2][2].getFillColor() == d2 && beads[1][3].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 3 && old_arr[1] == 2)
    {
        if ((beads[3][1].getFillColor() == d2 && beads[3][0].getFillColor() == Color::Transparent) || (beads[2][2].getFillColor() == d2 && beads[1][2].getFillColor() == Color::Transparent) || (beads[3][3].getFillColor() == d2 && beads[3][4].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 3 && old_arr[1] == 3)
    {
        if ((beads[2][2].getFillColor() == d2 && beads[1][1].getFillColor() == Color::Transparent) || (beads[3][2].getFillColor() == d2 && beads[3][1].getFillColor() == Color::Transparent) || (beads[2][3].getFillColor() == d2 && beads[1][3].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 3 && old_arr[1] == 4)
    {
        if ((beads[3][3].getFillColor() == d2 && beads[3][2].getFillColor() == Color::Transparent) || (beads[2][4].getFillColor() == d2 && beads[3][4].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 4 && old_arr[1] == 0)
    {
        if ((beads[4][1].getFillColor() == d2 && beads[4][2].getFillColor() == Color::Transparent) || (beads[3][1].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent) || (beads[3][0].getFillColor() == d2 && beads[2][0].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 4 && old_arr[1] == 1)
    {
        if ((beads[4][2].getFillColor() == d2 && beads[4][3].getFillColor() == Color::Transparent) || (beads[3][1].getFillColor() == d2 && beads[2][1].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 4 && old_arr[1] == 2)
    {
        if ((beads[4][1].getFillColor() == d2 && beads[4][0].getFillColor() == Color::Transparent) || (beads[4][3].getFillColor() == d2 && beads[4][4].getFillColor() == Color::Transparent) || (beads[3][1].getFillColor() == d2 && beads[2][0].getFillColor() == Color::Transparent) || (beads[3][2].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent) || (beads[3][3].getFillColor() == d2 && beads[2][4].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 4 && old_arr[1] == 3)
    {
        if ((beads[4][2].getFillColor() == d2 && beads[4][1].getFillColor() == Color::Transparent) || (beads[3][3].getFillColor() == d2 && beads[2][3].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else if (old_arr[0] == 4 && old_arr[1] == 4)
    {
        if ((beads[4][3].getFillColor() == d2 && beads[4][2].getFillColor() == Color::Transparent) || (beads[3][3].getFillColor() == d2 && beads[2][2].getFillColor() == Color::Transparent) || (beads[3][4].getFillColor() == d2 && beads[2][4].getFillColor() == Color::Transparent))
            return true;
        else
            return false;
    }
    else
        return false;
}

void turnn(int turn, Color& d1, Color& d2, string& PlayerName, const string& playerName1, const string& playerName2, int& bead)
{//to decide the bead

    if (turn % 2 == 0)
    {
        d1 = Color::Red;
        d2 = Color::Green;
        PlayerName = playerName1;
        bead = red;
    }
    else
    {
        d2 = Color::Red;
        d1 = Color::Green;
        PlayerName = playerName2;
        bead = green;
    }
}

void winner(RenderWindow& window, Color d1, string playerName1, string  playerName2, int& red, int& green)
{
    Texture texture;
    if (!texture.loadFromFile("./forwin.jpg"))
    {
        cout << "Load failed" << endl;
        system("pause");
    }

    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(50, 10);
    Text win("awd", font, 40);

    Text in("Go To Menu", font, 30);
    in.setPosition(450, 350);
    in.setFillColor(Color::Black);
    if (green == 0)
    {
        win.setString(playerName1 + " is winner! ");
        win.setPosition(400, 250);
        win.setOutlineThickness(3);
        win.setOutlineColor(Color::Black);
    }
    else
    {
        win.setString(playerName2 + " is winner! ");
        win.setPosition(400, 250);
        win.setOutlineThickness(3);
        win.setOutlineColor(Color::Black);
    }


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::Closed)
            {
                window.close();
            }


            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Space)
                {
                    Display(window);
                }
                else
                {
                    window.close();
                }
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePosition = Mouse::getPosition(window);    // Mouse Position

                // Check if any bead is clicked
                for (int i = 0; i < 5; ++i)
                {
                    for (int j = 0; j < 5; ++j)
                    {
                        if (in.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                        {
                            Display(window);
                        }
                    }
                }
            }
        }
        window.clear(Color::Black);
        // Draw Background

        window.draw(sprite);

        // Draw elements for coin toss
        window.draw(win);
        window.draw(in);
        window.display();
    }
}

void game(RenderWindow& window, const string& playerName1, const string& playerName2)
{
    int check = 0, checkCurr1 = 0, checkCurr2 = 0, checkCurr3 = 0, checkNext1 = 0, checkNext2 = 0, bead = 12;
    Color d1 = Color::Red;
    Color d2 = Color::Green;
    string PlayerName = "";
    Text p1(playerName1 + " - " + to_string(red), font, 30);
    Text p2(playerName2 + " - " + to_string(green), font, 30);

    p1.setFillColor(Color::Red);
    p1.setPosition(200, 70);
    p1.setOutlineThickness(3);
    p1.setOutlineColor(Color::Black);
    p2.setFillColor(Color::Green);
    p2.setPosition(400, 70);
    p2.setOutlineThickness(3);
    p2.setOutlineColor(Color::Black);
    Text playturn("", font, 100);
    int BeadPos[2] = {};
    int NewBeadPos[2] = {};
    while (bead_Check() == false)
    {
        checkCurr1 = 0;
        checkCurr2 = 0;
        checkCurr3 = 0;
        checkNext1 = 0;
        checkNext2 = 0;
        window.clear(Color::White);

        if (bead_Check() == true)
            break;

        drawLines(window);
        drawBeads(beads, window);

        //  Draw elements for coin toss
        window.draw(p1);
        window.draw(p2);

        if (check == 1)
        {
            checkNext2 = moveToNextPos(NewBeadPos, d1, d2);
            check = 0;
        }
        if (checkNext2 == 0)
        {
            turn++;
            turnn(turn, d1, d2, PlayerName, playerName1, playerName2, bead);
            playturn.setString(PlayerName + "'s Turn : ");
            playturn.setPosition(80, 200.f);
            while (checkCurr1 == 0 || checkCurr2 == 0 || checkCurr3 == 0)
            {
                BeadPos[0] = 0;
                BeadPos[1] = 0;
                getPlayerPos(window, playerName1, playerName2, BeadPos);
                cout << "\n " << PlayerName << " Old Bead Position : " << BeadPos[0] << " " << BeadPos[1] << endl;
                checkCurr1 = moveCheck1(BeadPos);
                checkCurr2 = moveCheck2(BeadPos, d1);
                checkCurr3 = moveCheck3(BeadPos, d1, d2);
                window.draw(playturn);
            }
        }
        else
        {
            BeadPos[0] = NewBeadPos[0];
            BeadPos[1] = NewBeadPos[1];
        }
        while (checkNext1 == 0)
        {
            NewBeadPos[0] = 0;
            NewBeadPos[1] = 0;
            getPlayerPos(window, playerName1, playerName2, NewBeadPos);
            cout << "\n " << PlayerName << " New Bead Position : " << NewBeadPos[0] << " " << NewBeadPos[1] << endl;
            if (d1 == Color::Red)
            {
                checkNext1 = implementation(BeadPos, NewBeadPos, d1, d2, check, green);
                if ((red == 0) || (green == 0))
                {
                    break;
                }
            }
            else {
                checkNext1 = implementation(BeadPos, NewBeadPos, d1, d2, check, red);
                if ((red == 0) || (green == 0))
                {
                    break;
                }
            }

            cout << checkNext1;
        }

        window.display();
        if ((red == 0) || (green == 0))
        {
            break;
        }
    }
    winner(window, d1, playerName1, playerName2, red, green);
}

void saveGameState(const string& fileName, CircleShape beads[5][5], const string& p1, const string& p2, Color d1, Color d2, int turn, int p1beads, int p2beads)
{
    ofstream outFile(fileName);

    if (outFile.is_open()) {
        string d1color = (d1 == Color::Red) ? "Red" : "Green";
        string d2color = (d2 == Color::Red) ? "Red" : "Green";

        outFile << p1 << " " << p2 << "\n";
        outFile << d1color << "\n";
        outFile << d2color << "\n";
        outFile << turn << "\n";
        outFile << p1beads << " " << p2beads << "\n";

        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                // Serialize based on color
                if (beads[i][j].getFillColor() == Color::Red) {
                    outFile << 1 << " ";
                }
                else if (beads[i][j].getFillColor() == Color::Green)
                {
                    outFile << 2 << " ";
                }
                else
                {
                    outFile << 0 << " ";
                }
            }
            outFile << '\n';
        }


        outFile.close();

        if (outFile.good()) {
            std::cout << "Game state saved successfully to " << fileName << "\n";
        }
        else {
            std::cerr << "Error: Unable to close file after writing\n";
        }
    }
    else {
        std::cerr << "Error: Unable to open file " << fileName << " for writing\n";
    }
}
void loadGameState(const string& fileName, CircleShape beads[5][5], string& p1, string& p2, Color& d1, Color& d2, int& turn, int& p1beads, int& p2beads)
{
    ifstream inFile(fileName);

    if (inFile.is_open()) {
        inFile >> p1 >> p2;

        string d1color, d2color;
        inFile >> d1color >> d2color;

        d1 = (d1color == "Red") ? Color::Red : Color::Green;
        d2 = (d2color == "Red") ? Color::Red : Color::Green;

        inFile >> turn;
        turn++;
        inFile >> p1beads >> p2beads;

        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                int beadColor;
                inFile >> beadColor;

                if (beadColor == 1) {
                    beads[i][j].setFillColor(Color::Red);
                }
                else if (beadColor == 2) {
                    beads[i][j].setFillColor(Color::Green);
                }
                else
                {
                    beads[i][j].setFillColor(Color::Transparent);
                }
            }
        }

        inFile.close();

        if (inFile.good()) {
            std::cout << "Game state loaded successfully from " << fileName << "\n";
        }
        else {
            std::cerr << "Error: Unable to close file after reading\n";
        }
    }
    else {
        std::cerr << "Error: Unable to open file " << fileName << " for reading\n";
    }
}
void start() {
    RenderWindow startwindow(VideoMode(800, 600), "12 Beads Game");
    Texture texture;
    if (!texture.loadFromFile("./bdg.jpg"))
    {
        cout << "Load failed" << endl;
        system("pause");
    }

    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(50, 10);
    while (startwindow.isOpen())
    {
        Event event;
        while (startwindow.pollEvent(event))
        {

            if (event.type == Event::Closed)
            {
                startwindow.close();
                break;
            }
            if (event.type == Event::MouseButtonPressed)
            {
                startwindow.close();
                break;
            }
        }
        startwindow.clear(Color::Black);
        startwindow.draw(sprite);
        startwindow.display();

    }
}

int main()
{
    start();
    LoadingBar();
    RenderWindow window(VideoMode(800, 600), "12 Beads Game");

    Display(window);

    return 0;
}