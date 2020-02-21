<template>
  <v-container>
    <v-row justify="center" align="center">
      <v-switch v-model="isLearning" color="primary" label="学習"></v-switch>
    </v-row>
    <v-row justify="center" align="center">
      <v-col cols="6">
        <DPad />
      </v-col>
      <v-col cols="6">
        <ManagementButtons />
      </v-col>
    </v-row>
  </v-container>
</template>

<script>
import DPad from '../components/DPad.vue'
import ManagementButtons from '../components/ManagementButtons.vue'

export default {
  components: {
    DPad,
    ManagementButtons
  },
  data() {
    return {
      isLearning: false
    }
  }
}
</script>
