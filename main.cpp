#include <iostream>
#include <SFML/Graphics.hpp>

class Display
{
private:
    int D_xres = 200;
    int D_yres = 150;
    int D_tileSize;
    int windowXres;
    int windowYres;
    sf::RectangleShape *pixelGrid;
public:
    Display(int xres, int yres)
    {
        windowXres = xres;
        windowYres = yres;
        pixelGrid = new sf::RectangleShape[D_xres * D_yres];
        if(xres > yres)
            D_tileSize = yres/D_yres;
        else
            D_tileSize = xres/D_xres;

        int xOffset = (xres - D_xres * D_tileSize)/2;
        int yOffset = (yres - D_yres * D_tileSize)/2;

        for(int iX = 0; iX < D_xres; ++iX)
        {
            for(int iY = 0; iY < D_yres; ++ iY)
            {
                pixelGrid[D_xres * iY + iX].setSize(sf::Vector2f(D_tileSize, D_tileSize));
                pixelGrid[D_xres * iY + iX].setFillColor(sf::Color::Black);
                pixelGrid[D_xres * iY + iX].setPosition(iX*D_tileSize + xOffset, iY*D_tileSize + yOffset);
            }
        }
    }

    int getDispSize()
    {
        return D_xres * D_yres;
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

    void draw(int x, int y, sf::Color color)
    {
        pixelGrid[D_xres * y + x].setFillColor(color);
    }
    void setRes(int xres, int yres)
    {
        D_xres = xres;
        D_yres = yres;
    }

    ~Display(){delete[] pixelGrid;}
};

using namespace std;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    int xres = 800;
    int yres = 600;
    sf::RenderWindow win(sf::VideoMode(xres, yres), "WOAH 3D!", sf::Style::Default, settings);
    Display disp(xres, yres);

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
        win.clear();

        for(int iY = 0; iY < disp.getYSize(); ++iY)
        {
            for(int iX = 0; iX < disp.getXsize(); ++iX)
            {
                if(iY % 2)
                {
                    if(iX % 2)
                        disp.draw(iX, iY, sf::Color::White);
                }
                else
                {
                    if(!(iX % 2))
                        disp.draw(iX, iY, sf::Color::White);
                }

            }
        }
        for(int i = 0; i < disp.getDispSize(); ++i)
        {
            win.draw(disp.getPixel(i));
        }
        win.display();
    }
    return 0;
}
