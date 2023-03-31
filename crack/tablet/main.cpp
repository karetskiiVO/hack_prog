#define _CRT_SECURE_NO_WARNINGS

#include "hack.h"

#include <SFML/Graphics.hpp>
#include <vector>

enum {
    ASK_ABOUT_FILE = 0,
    FILE_HACKED    = 1,
    FILE_NOT_EXIST = 2,
    HACK_DONE      = 3    
};

const size_t frnum = 31;

void getFrames (std::vector<sf::Texture>& arr);

int main () {
    sf::Vector2u resolution(800, 600);
    sf::Vector2u hackersize(500, 432);
    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "h@ck.exe");
    sf::String dialog[] = { "Oh, you forgot password?\nUnderstandble,...\nShow me PASSWORD.COM?" ,
                            "Why you can't, its already done."                      ,
                            "I can't see file"                                      ,
                            "It's looking strange.\nI don't know what is it."       ,
                            "Now you can use it"
                            };
    sf::Font font;
    font.loadFromFile("couriernew.ttf");
    char* prog = NULL;
    size_t progsize = 0;

    std::vector<sf::Texture> hackgif;
    sf::Sprite hacker;
    getFrames(hackgif);
    hacker.setPosition((resolution - hackersize).x / 2,  (resolution - hackersize).y / 2);

    size_t cnt = 0;
    size_t dialogit = 0;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    resolution = window.getSize();
                    break;
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::Enter) {
                        switch (dialogit) {
                            case 0:
                                progsize = uploadprogramm(&prog, "PASSWORD.COM");
                                if (!prog) {
                                    dialogit = 2;
                                    break;
                                }
                                
                                if (isnothacked(prog, progsize)) {
                                    dialogit = 4;
                                    makecrack();
                                } else if (ishacked(prog, progsize)) {
                                    dialogit = 1;
                                } else {
                                    dialogit = 3;
                                }
                                
                                free(prog);
                                prog = NULL;
                                break;
                            default:
                                dialogit = 0;                           
                        }
                    }
                    break;
                default:
                    break;
            }
        }

        window.clear();

        hacker.setTexture(hackgif[cnt++]);
        cnt %= hackgif.size();
        window.draw(hacker);

        sf::Text text;
        text.setString(dialog[dialogit]);
        text.setCharacterSize(22);
        text.setFillColor(sf::Color::Green);
        text.setOutlineColor(sf::Color::Green);
        text.setOutlineThickness(0.f);
        text.setPosition(resolution.x / 4,  resolution.y * 0.85);
        text.setFont(font);

        window.draw(text);
        window.display();
    }
    
    
    return 0;
}

void getFrames (std::vector<sf::Texture>& arr) {
    char frname[21] = "";

    for (size_t i = 0; i < frnum; i++) {
        sprintf(frname, "headsays\\frame_%lu.gif", i);
        sf::Texture buf;
        buf.loadFromFile(frname, sf::IntRect(0, 0, 500, 432));
        arr.push_back(buf);
    }
}
