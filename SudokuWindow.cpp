#include "SudokuWindow.hpp"

using namespace W;

SudokuWindow::SudokuWindow()
{
    valid=false;
    vector<int_bool> tmp = game.SendCurrentState(); //gamecoretol lekerjuk a jelenlegi allapotot
    int width=40;
    int tmp_x=0, tmp_y=0;
    for(int i=0; i<9; i++)
    {
        tmp_x += width;
        tmp_y=0;
        if(i%3==0) tmp_x += 10;
        tmp_x++;
        for(int j=0; j<9;j++)
        {
            tmp_y += width;
            SudokuNumberBox *nr;
            if(j%3==0) tmp_y += 10;
            if(tmp[i*9+j].value != 0)
            {
                nr = new SudokuNumberBox(tmp_y, tmp_x,width,width,{255,255,255},true,this,tmp[i*9+j].value,false);
            }
            else
            {
                nr = new SudokuNumberBox(tmp_y, tmp_x,width,width,{255,255,255},true,this,tmp[i*9+j].value,true);
            }
            widgets.push_back(nr);
            numbers.push_back(nr);

            tmp_y++;
        }
    }
    test = new Button(500,100,100,30,{173,216,230},false,this,"Visszaallit",[this](){ Reset();});
    message = new MessageBox(500,200,100,100,{0,191,255},false,this,"Te kis sudoku mester!",false);
    vector<string> lvl;
    lvl.push_back("Szint 1");
    lvl.push_back("Szint 2");
    lvl.push_back("Szint 3");
    lvl.push_back("Szint 4");
    lvl.push_back("Szint 5");
    levels = new DropDownList(650,100,100,{173,216,230},false,this,lvl,5);

    widgets.push_back(test);
    widgets.push_back(message);
    widgets.push_back(levels);

}


void SudokuWindow::Update()
{
    vector<int> tmp;
    for(int i=0;i<81;i++)
    {
        tmp.push_back(numbers[i]->getValue());
    }
    game.getNewState(tmp);

    if(game.getLevel()!=levels->getSelectedIndex())
    {
        message->Hide();
        game.ChooseLevel(levels->getSelectedIndex());
        vector<int_bool> friss;
        friss = game.SendCurrentState();

        for(size_t i =0; i< friss.size(); i++)
        {
            numbers[i]->setValue(friss[i].value);
            numbers[i]->validation(!friss[i].wrong);
            if(friss[i].value==0)
            {
                numbers[i]->change_modifiable(true);
            }
            else
            {
                numbers[i]->change_modifiable(false);
            }
        }
    }
    else{

    vector<int_bool> friss;
    friss = game.SendCurrentState();

    for(size_t i =0; i< friss.size(); i++)
    {
        numbers[i]->setValue(friss[i].value);
        numbers[i]->validation(!friss[i].wrong);
    }
    }
    if(game.win())
    {
        message->Show();
        for(size_t i =0 ; i<numbers.size();i++)
        {
            numbers[i]->change_modifiable(false);
        }
    }
}

void SudokuWindow::draw()
{
    if(!valid)
    {
        Update();
        gout<<move_to(0,0)<<color(0,191,255)<<box(800,600);
        for(Widget* &w:widgets)
        {
            w->draw();
        }
        if(focus!=-1)
            widgets[focus] -> draw();

        valid=true;
    }
}

void SudokuWindow::Reset()
{
    game.reset();
    message->Hide();
    vector<int_bool> friss;
    friss = game.SendCurrentState();

    for(size_t i =0; i< friss.size(); i++)
    {
        numbers[i]->setValue(friss[i].value);
        numbers[i]->validation(!friss[i].wrong);
        if(friss[i].value==0)
        {
            numbers[i]->change_modifiable(true);
        }
        else
        {
            numbers[i]->change_modifiable(false);
        }
    }
}
