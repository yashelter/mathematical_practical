#include "polynom.c"

int main()
{
    Polynom *p1, *p2, *p, *dev, *whit;
    create_polynom(&p1);
    add_koefficient(p1, 4);

    create_polynom(&p2);
    add_koefficient(p2, 4);
    add_koefficient(p2, 4);
    add_koefficient(p2, 6);

    
    div_polynoms(p2, p1, &dev);
    //printf("here\n");
    ///printf("%d \n", dev->first->value);
    print_polynom(dev);

   // ll res = 0;
    //calculate_polynom(p, &res, 1);
   // printf("\n%lld\n", res);
}