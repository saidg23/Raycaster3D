#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;

class Display
{
private:
    int D_xres = 400;
    int D_yres = 300;
    int D_tileSize;
    int windowXres;
    int windowYres;
    sf::RectangleShape *pixelGrid;
public:
    Display(int xres, int yres)
    {
        windowXres = xres;
        windowYres = yres;
        pixelGrid = new sf::RectangleShape[D_xres];
        if(xres > yres)
            D_tileSize = yres/D_yres;
        else
            D_tileSize = xres/D_xres;

        int xOffset = (xres - D_xres * D_tileSize)/2;
        int yOffset = (yres - D_yres * D_tileSize)/2;

        for(int iX = 0; iX < D_xres; ++iX)
        {
            pixelGrid[iX].setOrigin(sf::Vector2f(D_tileSize/2, D_tileSize/2));
            pixelGrid[iX].setSize(sf::Vector2f(D_tileSize, D_tileSize));
            pixelGrid[iX].setFillColor(sf::Color::Black);
            pixelGrid[iX].setPosition(iX*D_tileSize + xOffset, yres/2);
        }
    }

    int getXsize()
    {
        return D_xres;
    }

    int getYSize()
    {
        return D_yres;
    }

    sf::RectangleShape getPixel(int i)
    {
        return pixelGrid[i];
    }

    void drawVline(int xPos, int vLength, sf::Color color)
    {
        pixelGrid[xPos].setSize(sf::Vector2f(D_tileSize, vLength*D_tileSize));
        pixelGrid[xPos].setOrigin(sf::Vector2f(D_tileSize/2, (vLength*D_tileSize)/2));
        pixelGrid[xPos].setFillColor(color);
    }

    void clear()
    {
        for(int i = 0; i < D_xres; ++i)
            pixelGrid[i].setFillColor(sf::Color::Black);
    }


    ~Display(){delete[] pixelGrid;}
};

struct iVector
{
    int x = 0;
    int y = 0;
};

struct fVector
{
    double x = 0.0;
    double y = 0.0;
};

std::ostream& operator<<(std::ostream &out, iVector &vec)
{
    out << '(' << vec.x << ", " << vec.y << ')' << '\n';
    return out;
}

std::ostream& operator<<(std::ostream &out, fVector &vec)
{
    out << '(' << vec.x << ", " << vec.y << ')' << '\n';
    return out;
}

int main()
{
    int mapXres = 24;
    int mapYres = 24;
    int worldMap[mapXres][mapYres]=
    {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    int xres = 800;
    int yres = 600;
    sf::RenderWindow win(sf::VideoMode(xres, yres), "WOAH 3D!", sf::Style::Default, settings);
    win.setFramerateLimit(60);
    Display disp(xres, yres);

    double playerAngle = 0.0;
    fVector playerPos{1.0, 1.0};
    fVector playerDir{sin(playerAngle*3.141592/180.0), sin((90-playerAngle)*3.141592/180.0)};
    cout << playerDir;
    while(win.isOpen())
    {
        sf::Event event;
        while(win.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                win.close();
            }
        }

        static iVector tilePos;
        tilePos = {int(playerPos.x), int(playerPos.y)};

        fVector rayDir = playerDir;

        static double deltaDistX;
        static double deltaDistY;
        deltaDistX = sqrt(1 + (playerDir.y*playerDir.y)/(playerDir.x*playerDir.x));
        deltaDistY = sqrt(1 + (playerDir.x*playerDir.x)/(playerDir.y*playerDir.y));

        static double sideDistX;
        static double sideDistY;
        sideDistX = (tilePos.x + 1 - playerPos.x) * deltaDistX;
        sideDistY = (tilePos.y + 1 - playerPos.y) * deltaDistY;

        static iVector nextTile;
        nextTile = tilePos;

        int hit = 0;
        int side = 0;
        while(hit == 0)
        {
            if(sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                tilePos.x += 1;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                tilePos.y += 1;
                side = 1;
            }
            if(worldMap[tilePos.x][tilePos.y])
                hit = 1;
        }

        int wallDistance;

        if(side == 0)
            wallDistance = (tilePos.x - playerPos.x + (1 - nextTile.x)/2) / rayDir.x;
        else
            wallDistance = (tilePos.y - playerPos.y + (1 - nextTile.y)/2) / rayDir.y;

        static int lineHeight;
        lineHeight = int(yres / wallDistance);

        disp.drawVline(200, lineHeight, sf::Color::White);

        for(int i = 0; i < disp.getXsize(); ++i)
            win.draw(disp.getPixel(i));

        win.display();
        win.clear();
        disp.clear();
    }
    return 0;
}
