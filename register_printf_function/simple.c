// code: https://www.gnu.org/software/libc/manual/html_node/Printf-Extension-Example.html
// doc: https://www.gnu.org/software/libc/manual/html_node/Customizing-Printf.html

#include <stdio.h>
#include <stdlib.h>
#include <printf.h>

typedef struct
{
  char *name;
}
Widget;

int print_widget (FILE *stream, const struct printf_info *info, const void *const *args)
{
  const Widget *w;
  char *buffer;
  int len;

  w = *((const Widget **) (args[0]));
  len = asprintf (&buffer, "<Widget %p: %s>", w, w->name);
  if (len == -1)
    return -1;

  len = fprintf (stream, "%*s", (info->left ? -info->width : info->width), buffer);

  free (buffer);
  return len;
}


int print_widget_arginfo (const struct printf_info *info, size_t n, int *argtypes)
{
  if (n > 0)
    argtypes[0] = PA_POINTER;
  return 1;
}


int main ()
{
  Widget mywidget;
  mywidget.name = "mywidget";

  register_printf_function ('W', print_widget, print_widget_arginfo);

  printf ("|%W|\n", &mywidget);
  printf ("|%35W|\n", &mywidget);
  printf ("|%-35W|\n", &mywidget);

  return 0;
}
