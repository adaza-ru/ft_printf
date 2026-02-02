
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#define RED   "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

// Para capturar la salida de ft_printf necesitaremos usar un truco con pipes o 
// simplemente confiar en la comparación visual estricta y el retorno.
// Pero para este main, vamos a usar una comparación visual clara:

void test(char *name, char *format, ...)
{
    va_list args1, args2;
    va_start(args1, format);
    va_start(args2, format);

    // Usamos %s para el nombre, así evitamos que printf intente interpretar los %% del nombre
    printf(YELLOW "Test: %s | Format: \"%s\"\n" RESET, name, format);
    
    // Original
    printf("  Orig: |");
    fflush(stdout); // <--- OBLIGAMOS A IMPRIMIR LO ANTERIOR
    int r1 = vprintf(format, args1);
    fflush(stdout); // <--- OBLIGAMOS A IMPRIMIR EL RESULTADO
    printf("|\n");

    // Tu ft_printf
    printf("  Mine: |");
    fflush(stdout); // <--- Vaciamos antes de que entre tu write
    int r2 = ft_printf(format, args2);
    // No hace falta fflush aquí porque ft_printf usa write (es directo)
    printf("|\n\n");

    va_end(args1);
    va_end(args2);

    if (r1 == r2)
        printf(GREEN "  [OK] Retorno: %d\n" RESET, r1);
    else
        printf(RED "  [FAIL] Retorno diff! Orig: %d, Mine: %d\n" RESET, r1, r2);
    printf("-------------------------------------------\n");
}

int main()
{
    printf("\n=== INICIO DE TESTS CRÍTICOS ===\n\n");

    // 1. Porcentajes con Width y Flags
    test("%%5%%", "%5%");
    test("%%-5%%", "%-5%");
    test("%%05%%", "%05%");
    test("%%-05%%", "%-05%");

    // 2. Strings NULL con Precisión (El "recorte")
    test("NULL .3s", "%.3s", NULL);
    test("NULL 3.1s", "%3.1s", NULL);
    test("NULL 9.1s", "%9.1s", NULL);
    test("NULL -9.1s", "%-9.1s", NULL);
    test("NULL 50.2s", "%50.2s", NULL);

    // 3. Casos de Porcentaje Encadenado
    test("Percent 12", "percent 2 %12%");
    test("Percent -12", "percent 3 %-12%");

    // 4. El caso vacío
    test("Single percent", "%");

    return 0;
}