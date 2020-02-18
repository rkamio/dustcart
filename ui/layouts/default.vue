<template>
  <v-app dark>
    <v-app-bar v-if="!$vuetify.breakpoint.xs" :clipped-left="clipped" fixed app>
      <v-btn text icon @click="$router.push('/')">
        <v-icon>mdi-tank</v-icon>
      </v-btn>
      <v-toolbar-title>PageTitle</v-toolbar-title>
      <v-spacer></v-spacer>
      <v-btn text icon @click="$router.push('/setting')">
        <v-icon>mdi-wrench</v-icon>
      </v-btn>
    </v-app-bar>

    <v-content>
      <v-container>
        <nuxt />
      </v-container>
    </v-content>

    <v-bottom-navigation
      v-if="$vuetify.breakpoint.xs"
      app
      :value="activeBtn"
      grow
      max-height="50px"
    >
      <v-btn @click="$router.push('/')">
        <span>操縦</span>
        <v-icon>mdi-tank</v-icon>
      </v-btn>
      <v-btn @click="$router.push('/setting')">
        <span>設定</span>
        <v-icon>mdi-wrench</v-icon>
      </v-btn>
    </v-bottom-navigation>
    <v-footer v-else class="font-weight-medium" paddless>
      <v-col class="text-center" cols="12">
        &copy; {{ new Date().getFullYear() }} - rkamy
      </v-col>
    </v-footer>
  </v-app>
</template>

<!-- <script>
export default {
  
}
</script> -->
