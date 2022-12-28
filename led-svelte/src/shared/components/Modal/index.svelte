<script lang="ts">
  import "./index.css"
  export let isOpened:boolean;
</script>

{#if isOpened }
<div class="modal-background" >
  <div class="modal-content"><slot/></div>
</div>
{/if}
