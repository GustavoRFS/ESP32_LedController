<script lang="ts">
  import Textfield from "@smui/textfield";
  import Button from "@smui/button";
  import Tooltip, { Wrapper } from "@smui/tooltip";
  import Modal from "../Modal/index.svelte";
  let value = 150;

  export let isOpened: boolean;
  export let toggleModal: () => void;
</script>

<Modal {isOpened}>
  <div
    style="display:flex;flex-direction:column;justify-content:center;align-items:center;padding:50px 0px"
  >
    <Wrapper>
      <Textfield
        type="number"
        variant="outlined"
        bind:value
        label="Número de Leds"
        style="min-width: 250px;"
      /><Tooltip
        >Se você cortou a fita, altere a quantidade de leds para que a fita
        funcione corretamente.</Tooltip
      >
    </Wrapper>
    <div style="margin-top:20px;">
      <Button style="width:100px;" variant="raised" on:click={console.log}
        >Salvar</Button
      >
      <Button
        style="width:100px;margin-left:8px"
        variant="text"
        on:click={toggleModal}>Fechar</Button
      >
    </div>
  </div>
</Modal>
