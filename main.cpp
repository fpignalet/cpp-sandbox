//
// Created by franc on 30.01.2019.
//

#include <map>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

class Item
{
public:
    Item(std::string* ptag1, std::string* ptag2, std::vector<std::string>* ptagsM){
        assert(NULL != ptag1);
        assert(NULL != ptag2);
        assert(NULL != ptagsM);

        this->tag1 = *ptag1;
        this->tag2 = *ptag2;
        std::vector<std::string>* ptags_ = (std::vector<std::string>*)ptagsM;
        for (std::vector<std::string>::iterator it = ptags_->begin(); it != ptags_->end(); it++){
            this->tagsM.push_back(*it);
        }
    }

    inline std::string& getTag1() { return this->tag1; }
    inline std::string& getTag2() { return this->tag2; }
    inline std::vector<std::string>& getTagsM() { return this->tagsM; }

private:
    std::string tag1;
    std::string tag2;
    std::vector<std::string> tagsM;
};

class TestCollection: std::vector<Item>
{
public:
    void addItem(Item &item){
        this->push_back(item);
    }
    void deleteItemByT1(Item &item){
        this->erase(
            std::remove_if(
                this->begin(), this->end(),
                // LAMBDA --------------------------------------
                [ item ](Item & targ) -> bool {
                    Item & item_ = (Item&)item;
                    return (0 == item_.getTag1().compare(targ.getTag1().c_str()));
                }
            )
        );
    }

    Item *searchByTag1(std::string *ptag){
        std::vector<Item>::iterator it = std::find_if(
            this->begin(), this->end(),
            // LAMBDA --------------------------------------
            [ ptag ](Item & item) -> bool {
                std::cout << ptag << std::endl;
                return (0 == item.getTag1().compare(ptag->c_str()));
            }
        );

        if(this->end() != it) {
            return it.base();
        }
        else {
            return NULL;
        }
    }
    Item *searchByTag2(std::string *ptag){
        std::vector<Item>::iterator it = std::find_if(
            this->begin(), this->end(),
            // LAMBDA --------------------------------------
            [ ptag ](Item & item) -> bool {
                return (0 == item.getTag2().compare(ptag->c_str()));
            }
        );

        if(this->end() != it) {
            return it.base();
        }
        else {
            return NULL;
        }
    }
    Item *searchByTagsM(std::string *ptag){
        std::vector<Item>::iterator it = std::find_if(
            this->begin(), this->end(),
            // LAMBDA --------------------------------------
            [ ptag ](Item & item) -> bool {
                std::vector<std::string>::iterator sub = std::find_if(
                    item.getTagsM().begin(),
                    item.getTagsM().end(),
                    // LAMBDA --------------------------------------
                    [ ptag ](std::string &str) -> bool {
                        return (0 == str.compare(ptag->c_str()));
                    }
                );

                return (item.getTagsM().end() != sub);
            }
        );

        if(this->end() != it) {
            return it.base();
        }
        else {
            return NULL;
        }
    }

};

int main(int argc, char **argv)
{
    TestCollection test;

    {
        std::string tag1 = "title1";
        std::string tag2 = "text1";
        std::string tag = "tag1";
        std::vector<std::string> tags;
        tags.push_back(tag);

        Item item(&tag1, &tag2, &tags);
        test.addItem(item);
    }

    {
        std::string tag1 = "title2";
        std::string tag2 = "text2";
        std::string tag = "tag2";
        std::vector<std::string> tags;
        tags.push_back(tag);

        Item item(&tag1, &tag2, &tags);
        test.addItem(item);
    }

    {
        std::string tag1 = "title1";
        std::string tag2 = "text1";
        std::string tagM = "tag1";

        Item *pres = NULL;
        pres = test.searchByTag1(&tag1);
        pres = test.searchByTag2(&tag2);
        pres = test.searchByTagsM(&tagM);
        if(NULL != pres) {
            std::cout << "DELETED 1" << std::endl;
            test.deleteItemByT1(*pres);
        }

    }

    {
        std::string tag1 = "title1";
        std::string tag2 = "text1";
        std::string tagM = "tag1";

        Item *pres = NULL;
        pres = test.searchByTag1(&tag1);
        pres = test.searchByTag2(&tag2);
        pres = test.searchByTagsM(&tagM);
        if(NULL == pres) {
            std::cout << "NOT DELETED 2" << std::endl;
        }

    }

    return 0;
}
