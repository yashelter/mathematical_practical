#include "Mail.c"


int main() {
    Post post;
    post.mails = (Mail **) malloc(sizeof(Mail *) * MIN_BUF);
    post.adress = (Adress *) malloc(sizeof(Adress) * MIN_BUF);
    post.mails_cnt = 0;
    post._buffer = MIN_BUF;

    //Mail *mail;
    //statements stm = create_mail(&post, &mail);
    //printf("%d\n", stm);
    //print_mail(mail);

    run(&post);
    delete_post(&post);
    return 0;
}