from django.db import models

# Create your models here.


class Dustcart(models.Model):
    name = models.CharField(max_length=32)
    ip_address = models.CharField(max_length=32)
    status = models.CharField(max_length=32)
    builded_at = models.DateTimeField('date real dustcar builded')
    created_at = models.DateTimeField('date record inserted')
    updated_at = models.DateTimeField('date record updated')

# class Setting(models.Model):
    # About Manual-Handle setting like inertia
