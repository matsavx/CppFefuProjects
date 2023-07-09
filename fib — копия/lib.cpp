int Fibbanachy (int i)
{
    if (i<1) return 0;
    if (i==1) return 1;
    return (Fibbanachy (i-1) + Fibbanachy (i-2));
}
