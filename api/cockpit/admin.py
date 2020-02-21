from django.contrib import admin

# Register your models here.

from .models import Dustcart


@admin.register(Dustcart)
class Dustcart(admin.ModelAdmin):
    pass
